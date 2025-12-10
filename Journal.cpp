#include "Journal.h"


Journal::Journal(const std::string& t, int v) : title(t), volume(v) {}


std::string Journal::info() const {
	return "Revista: " + title + ", Volumen: " + std::to_string(volume);
}


std::string Journal::getTitle() const { return title; }
int Journal::getVolume() const { return volume; }