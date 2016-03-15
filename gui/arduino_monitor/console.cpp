#include "console.h"

// Construtor do console
Console::Console(){

	// Muda a largura do cursor,
	// para ficar mais "quadrado"
	int cursor_value = 10;
	this->setCursorWidth(cursor_value);
	this->setCurrentFont(QFont("Consolas", cursor_value));

	QPalette colors = this->palette();
	colors.setColor(QPalette::Base, Qt::black);
	colors.setColor(QPalette::Text, Qt::green);
	colors.setColor(QPalette::AlternateBase, Qt::white);
	colors.setColor(QPalette::Highlight, Qt::blue);
	colors.setColor(QPalette::HighlightedText, Qt::white);
	this->setPalette(colors);

	this->lineWrapMode();
}
