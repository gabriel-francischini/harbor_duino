#include "console.h"


// Construtor do console
Console::Console(){

	// Não permitir entrada de texto enquanto
	// estiver iniciando
	setReadOnly(true);
	setUpCommands();
	setUp();
	greetings();
	comm_online = false;
	setReadOnly(false);

}




// Função responsável por iniciar o console
void Console::setUp(){

	// Define o símbolo que significa que o terminal
	// está desocupado
	awaiting = '>';

	// Muda a largura e a fonte do cursor
	int cursor_value = 10;
	setCursorWidth(cursor_value);
	setCurrentFont(QFont("Consolas", cursor_value));

	// Cria uma paleta e guarda as cores
	// que tornam o console mais amigável
	QPalette colors = this->palette();
	colors.setColor(QPalette::Base, Qt::black);
	colors.setColor(QPalette::Text, Qt::green);
	colors.setColor(QPalette::AlternateBase, Qt::white);
	colors.setColor(QPalette::Highlight, Qt::blue);
	colors.setColor(QPalette::HighlightedText, Qt::white);

	// Aplica a paleta de cores ao console
	setPalette(colors);

	// Define um limite de caracteres por linha
	setLineWrapMode(QTextEdit::WidgetWidth);

	// Impede de abrir um menu ao clicar com o lado
	// direito do mouse
	setContextMenuPolicy(Qt::PreventContextMenu);

}



void Console::show(QString string){
	setReadOnly(true);
	append(string.prepend("  "));
	append(awaiting);
	setReadOnly(false);
}

void Console::showAwaiting(){
	setReadOnly(true);
	insertPlainText(awaiting);
	setReadOnly(false);
}


void Console::greetings(){
	show(tr("Iniciando o terminal..."));
}


// Função responsável por lidar com as teclas
// digitadas através do teclado
void Console::keyPressEvent(QKeyEvent *key){

	// Obtém o cursor do console
	QTextCursor cursor = textCursor();

	// Obtem o texto total do console
	// ( o log e a linha atual )
	QString text = this->toPlainText();

	// Descobre onde está localizada a linha
	// onde o usuário pode entrar comandos
	int last_line = text.lastIndexOf(QString("\n").append(awaiting)) + 1;

	// Caso o usuário esteja tentando deletar
	// ou apagar qualquer texto que não seja
	// a linha na qual ele pode digitar...
	if (
		 ( key->key() == Qt::Key_Backspace ||
		   key->key() == Qt::Key_Delete ) &&
		   cursor.position() <= last_line ){

				// ... então coloca o cursor de volta
				// à última linha
				cursor.setPosition(text.length());
				setTextCursor(cursor);

				// ...e ignora
				return;
	}


	// Caso o cursor não esteja na última linha,
	// coloque-o nela
	if (cursor.position() <= last_line)
		cursor.setPosition(last_line + 1,QTextCursor::MoveAnchor);

	// Se estiver tentando juntar a linha
	// atual com a anterior, ignore
	if (cursor.position() == last_line + 1 &&
		 (key->key() == Qt::Key_Left ||
		  key->key() == Qt::Key_Backspace) )
		return;

	// Se estiver tentando subir à linha anterior, ignore
	if ( key->key() == Qt::Key_Up ) return;

	// Atualize o cursor
	setTextCursor(cursor);

	// Caso seja enter, processe o comando
	// da forma que deve ser processado
	if (key->key() == Qt::Key_Return || key->key() == Qt::Key_Enter){
		QString last_command = text.remove(0, last_line + 1);
		last_command = last_command.toLower().simplified();
		switch (implemented_commands.indexOf(last_command)){
			case 0:
			case 12:
				clear();
				showAwaiting();
				break;
			case 8:
			case 9:
			case 10:
				if (comm_online) show(tr("Ligado\n"));
				else show(tr("Desligado\n"));
				break;
			case 11:
				clear();
				setReadOnly(true);
				break;
			default:
				if (comm_online)
					show(communicator->execute(last_command));
				else
					show(tr("Comando desconhecido.\n"));
				break;
		}
		return;
	}

	// Se não for nenhum dos casos anteriores,
	// siga o procedimento padrão
	QTextEdit::keyPressEvent(key);

}


void Console::setUpCommands(){
	implemented_commands
			<< "limpar terminal" // 0
			<< "definir terminal fundo cor" // 1
			<< "definir terminal texto cor" // 2
			<< "definir terminal texto tamanho" // 3
			<< "definir terminal cursor tamanho" // 4
			<< "definir terminal fundo selecionado cor" // 5
			<< "definir terminal texto selecionado cor" // 6
			<< "definir terminal estilo" // 7
			<< "comunicador ligado?" // 8
			<< "comunicador online?" // 9
			<< "comm_online" // 10
			<< "sair" // 11
			<< "limpar" // 12
			;
}


void Console::setCommunicator(Communicator *communicator){
	this->communicator = communicator;
	comm_online = true;
}


bool Console::isCommOnline(){
	return comm_online;
}


Communicator Console::getCommunicator(){
	return *communicator;
};

void Console::unsetCommunicator(){
	comm_online = false;
}
