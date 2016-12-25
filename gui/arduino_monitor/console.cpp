#include "console.h"


// Construtor do console
Console::Console(QWidget *parent) {

	// Define que o console é "filho" de quem o criou
	setParent(parent);

	// Não permitir entrada de texto enquanto
	// estiver iniciando
	setReadOnly(true);

	// Define a lista de comandos aceitos ou não
	setUpCommands();

	// Inicia o console propriamente
	setUp();

	// Mostra a mensagem inicial
	greetings();

	// Voltar a permitir a entrada de texto
	setReadOnly(false);

}

Console::~Console(){

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
	// que tornam o console mais "amigável"
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


// Função slot responsável por mostrar
// textos na interface do console
void Console::show(QString string){

	// Impede a digitação enquanto edita o console
	this->setReadOnly(true);

	// Adiciona uma identação antes do texto a ser mostrado
	this->insertPlainText(string.prepend("  "));

	this->append(awaiting);

	// Volta a permitir a digitação
	this->setReadOnly(false);
	return;
}

void Console::external_show(QString string){

	// Impede a digitação enquanto edita o console
	this->setReadOnly(true);

	// Obtem o texto total do console
	// (o log e a linha atual)
	QString text = this->toPlainText();

	if(text.endsWith(QChar('\n'), Qt::CaseInsensitive) ||
	   text.endsWith(QChar('\r'), Qt::CaseInsensitive) ||
	   text.endsWith(QChar('\t'), Qt::CaseInsensitive) ||
	   text.endsWith(QChar('\v'), Qt::CaseInsensitive) ||
	   text.endsWith(QChar('\0'), Qt::CaseInsensitive)  ){

		// Adiciona uma identação antes do texto a ser mostrado
		// e em seguida o adiciona ao texto atual
		this->append(string.prepend("  "));

	}
	else {
		// Descobre onde está localizada a linha
		// onde o usuário pode entrar comandos
		int last_line = text.lastIndexOf(QString("\n").append(awaiting));

		// Já que ao mudar o texto o cursor atual
		// também é modificado, é necessário saber o
		// estado do cursor anterior à mudança
		QTextCursor cursor = this->textCursor();
		int cursor_position = this->textCursor().position();

		// Adiciona uma identação anterior e
		// uma nova linha posterior à mensagem
		// e em seguida a adiciona ao texto entre
		// a linha do usuário e a anterior
		text = text.insert(last_line, string.prepend("  ").append("\n"));

		// Define que o texto do console
		// passará a ser esse novo texto
		this->setText(text);

		// Define onde o cursor deveria estar
		// e o coloca no seu lugar natural
		cursor_position += string.length();
		cursor.setPosition(cursor_position, QTextCursor::MoveAnchor);
		this->setTextCursor(cursor);
	}


		// Volta a permitir a digitação
		this->setReadOnly(false);
		return;

}

// Função responsável por adicionar
// o cursor de inatividade
void Console::showAwaiting(){
	setReadOnly(true);
	insertPlainText(awaiting);
	setReadOnly(false);
}


// Mensagem de boas-vindas
void Console::greetings(){
	show(tr("Iniciando o terminal...\n"));
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
		last_command = last_command.simplified();
		switch (implemented_commands.indexOf(last_command)){
			case 0:
			case 12:
				clear();
				show(QString(""));
				break;
			case 8:
			case 9:
			case 10:
				show(tr("Ligado"));
				break;
			case 11:
				clear();
				setReadOnly(true);
				break;
			default:
				append("");
				show(communicator->execute(last_command));
				break;
		}
		return;
	}

	// Se não for nenhum dos casos anteriores,
	// siga o procedimento padrão de aceitar
	// a entrada como se fosse um texto
	QTextEdit::keyPressEvent(key);

}


// Define os comandos conhecidos
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
}


bool Console::isCommOnline(){
	return true;
}


Communicator* Console::getCommunicator(){
	return communicator;
};
