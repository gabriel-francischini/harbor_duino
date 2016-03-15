#include "console.h"


// Construtor do console
Console::Console(){

	// Não permitir entrada enquanto
	// estiver iniciando
	setReadOnly(true);
	setUp();
	greetings();
	setReadOnly(false);

}




// Função responsável por iniciar o console
void Console::setUp(){

	// Muda a largura e a fonte do cursor
	int cursor_value = 10;
	setCursorWidth(cursor_value);
	setCurrentFont(QFont("Consolas", cursor_value));

	// Cria uma paleta e guarda as cores
	// que tornam o console mais old-school
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
	append(string);
	append(awaiting);
	setReadOnly(false);
}


void Console::greetings(){
	show(tr("Iniciando terminal..."));
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

	// Se não for nenhum dos casos anteriores,
	// siga o procedimento padrão
	QTextEdit::keyPressEvent(key);

	if (key->key() == Qt::Key_Enter){

	}
}
