//
// Created by consent_ on 07/05/25.
//

#include "CircleWithText.h"

#include <iostream>

#include <cmath>
#include <ranges>


template<typename VectorType, typename DivisorType>
sf::Vector2<VectorType> cwt::CircleWithText::vectorDivider(const sf::Vector2<VectorType> &v, DivisorType divisor)
{
	return std::move(sf::Vector2<VectorType> {v.x / divisor, v.y / divisor});
}

sf::Color cwt::CircleWithText::ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor)
{
	auto convert = [](const float ImGuiColorChannel) -> std::uint8_t
	{
		if (ImGuiColorChannel <= 1.0f && ImGuiColorChannel >= 0.0f)
			return static_cast<std::uint8_t>(std::round(ImGuiColorChannel * 255.f));

		throw std::invalid_argument("Invalid ImGuiColor");
	};

	return sf::Color{
		convert(ImGuiColor[0]),
		convert(ImGuiColor[1]),
		convert(ImGuiColor[2]),
	};
}

std::array<float, 3> cwt::CircleWithText::SFMLColorToImGui(const sf::Color& color)
{
	return std::array{
		static_cast<float>(color.r) / 255.f,
		static_cast<float>(color.g) / 255.f,
		static_cast<float>(color.b) / 255.f,
	};
}

int cwt::CircleWithText::randomInt(std::mt19937_64 &gen, const int min, const int max) {
	std::uniform_int_distribution distribution(min, max);
	return distribution(gen);
}

float cwt::CircleWithText::randomFloat(std::mt19937_64 &gen, const float min, const float max) {
	std::uniform_real_distribution distribution(min, max);
	return distribution(gen);
}

sf::Color cwt::CircleWithText::invertColor(const sf::Color &color)
{
	return sf::Color{
		static_cast<std::uint8_t>(255 - color.r),
		static_cast<std::uint8_t>(255 - color.g),
		static_cast<std::uint8_t>(255 - color.b),
		color.a
	};
}

void cwt::CircleWithText::processAxisCollision(
	const float CenterPos,
	const float Radius,
	float &velocity,
	float axis
)
{
	if (CenterPos - Radius <= 0.f || CenterPos + Radius >= axis)
		velocity *= -1;
}

void cwt::CircleWithText::centeringText() {
	std::cout << "CircleWithText::centeringText()" << std::endl;
	this->textCenter = circle.getLocalBounds().getCenter() - text.getLocalBounds().getCenter();
}

///////////////////////////////////////////////////
////	КОНСТУКТОР
//////////////////////////////////////////////////

cwt::CircleWithText::CircleWithText(
	const sf::Font& font,
	const std::string& textString,
	float radius,
	int pointCount,
	const sf::Vector2f& position,
	const sf::Vector2f& velocity
	)
	: circle{radius, static_cast<std::size_t> (pointCount)}
	, text(font, textString, 24)
	, velocity(velocity)
{
	std::cout << "CircleWithText::CircleWithText()" << std::endl;
	centeringText();
	this->setPosition(position);
	isCircleDrawn = isTextDrawn = true;

	//TODO: Сделать систему инвертирования цвета букв относительно самой фигуры

}

cwt::CircleWithText::CircleWithText(
	std::mt19937_64 &gen,
	const sf::Font &font,
	const std::string &textString,
	const sf::Vector2u &screenSize
)
	: circle(randomFloat(gen, 30.f, 200.f), randomInt(gen, 32, 64))
	, text(font, textString, 24)
{
std::cout << "CircleWithText::CircleWithText()" << std::endl;
	centeringText();
	this->setPosition({randomFloat(gen, 0.f, screenSize.x), randomFloat(gen, 0.f, screenSize.y)});
	this->setVelocity(sf::Vector2f{randomFloat(gen, -5.f, 5.f), randomFloat(gen, -5.f, 5.f)});
	this->setCircleFillColor(sf::Color{
		static_cast<std::uint8_t>(randomInt(gen, 0, 255)),
		static_cast<std::uint8_t>(randomInt(gen, 0, 255)),
		static_cast<std::uint8_t>(randomInt(gen, 0, 255)),
	});
	isCircleDrawn = isTextDrawn = true;
}
///////////////////////////////////////////////////
////	СЕТТЕРЫ
//////////////////////////////////////////////////

void cwt::CircleWithText::setCircleFillColor(const std::array<float, 3>& ImGuiColor) {
	std::cout << "CircleWithText::setFillColor()" << std::endl;
	setCircleFillColor(ImGuiColorToSFMLColor(ImGuiColor));
}

void cwt::CircleWithText::setCircleFillColor(const sf::Color& color) {
	this->circle.setFillColor(color);
}

void cwt::CircleWithText::setPosition(const sf::Vector2f &position) {
	std::cout << "CircleWithText::setPosition()" << std::endl;
	circle.setPosition(position);
	text.setPosition(position + textCenter);
}

void cwt::CircleWithText::setRadius(float radius) {
	std::cout << "CircleWithText::setRadius()" << std::endl;
	circle.setRadius(radius);
	centeringText();
}

void cwt::CircleWithText::setPointCount(const std::size_t& pointCount) {
	return circle.setPointCount(pointCount);
}

void cwt::CircleWithText::setVelocity(const sf::Vector2f &velocity) {
	this->velocity = velocity;
}

void cwt::CircleWithText::setVelocity(const std::array<float, 2> &velocity) {
	setVelocity(sf::Vector2f{velocity[0], velocity[1]});
}

void cwt::CircleWithText::setString(const std::string &text)
{
	this->text.setString(text);
	centeringText();
}


///////////////////////////////////////////////////
////	ГЕТТЕРЫ
//////////////////////////////////////////////////

std::array<float, 3> cwt::CircleWithText::getImGuiFillColor() const {
	return SFMLColorToImGui(this->circle.getFillColor());
}

std::array<float, 2> cwt::CircleWithText::getImGuiVelocity() const {
	return {velocity.x, velocity.y};
}
sf::Vector2f cwt::CircleWithText::getPosition() const {
	return circle.getPosition();
}

float cwt::CircleWithText::getRadius() const {
	return circle.getRadius();
}

sf::Vector2f cwt::CircleWithText::getVelocity() const {
	return velocity;
}

std::size_t cwt::CircleWithText::getPointCount() const {
	return circle.getPointCount();
}

std::string cwt::CircleWithText::getString() const {
	return text.getString();
}


void cwt::CircleWithText::move() {
	std::cout << "CircleWithText::move()" << std::endl;
	this->setPosition(this->circle.getPosition() + velocity);
}

void cwt::CircleWithText::draw(sf::RenderWindow& window) const {
    if (isCircleDrawn) window.draw(circle);
    if (isTextDrawn) window.draw(text);
}

void cwt::CircleWithText::processScreenCollision(const sf::Vector2u &windowSize)
{
	processAxisCollision(
		circle.getGlobalBounds().getCenter().x,
		circle.getRadius(),
		velocity.x,
		windowSize.x
	);

	processAxisCollision(
		circle.getGlobalBounds().getCenter().y,
		circle.getRadius(),
		velocity.y,
		windowSize.y
	);
}

///////////////////////////////////////////////////
////	ImGuiLoopHandler
//////////////////////////////////////////////////

cwt::CircleWithText cwt::getElement(unsigned selectedIndex, const std::list<CircleWithText> &lsCircles)
{
	if (selectedIndex < lsCircles.size()) {
		auto it = lsCircles.begin();
		std::advance(it, selectedIndex);
		return *it;
	}
	std::cerr << "List is out of range:" << lsCircles.size() << "<" << selectedIndex << std::endl;
	throw std::out_of_range("List out of range");
}

cwt::CircleWithText& cwt::getElementRef(unsigned selectedIndex, std::list<CircleWithText> &lsCircles)
{
	auto it = lsCircles.begin();
	if (selectedIndex < lsCircles.size()) {
		std::advance(it, selectedIndex);
	}
	return *it;
}

cwt::ImGuiLoopHandler::ImGuiLoopHandler(unsigned selectedIndex, const CircleWithText &circle)
	: currentIndex(selectedIndex)
	, radius(circle.getRadius())
	, pointCount(circle.getPointCount())
	, velocity(circle.getVelocity())
	, textString(circle.getString())
	, ImGuiCircleFillColor(circle.getImGuiFillColor())
	, isCircleDrawn(circle.isCircleDrawn)
	, isTextDrawn(circle.isTextDrawn)
{
}

cwt::ImGuiLoopHandler::ImGuiLoopHandler(unsigned selectedIndex, const std::list<CircleWithText> &lsCircles)
	: ImGuiLoopHandler(selectedIndex, getElement(selectedIndex, lsCircles)) {}

cwt::ImGuiLoopHandler & cwt::ImGuiLoopHandler::operator=(const CircleWithText &circle)
{
	radius = circle.getRadius();
	pointCount = circle.getPointCount();
	//position = circle.getPosition();
	velocity = circle.getVelocity();
	textString = circle.text.getString();
	ImGuiCircleFillColor = circle.getImGuiFillColor();
	isCircleDrawn = circle.isCircleDrawn;
	isTextDrawn = circle.isTextDrawn;

	return *this;
}

void cwt::ImGuiLoopHandler::pushData(unsigned selectedIndex, const CircleWithText &circle)
{
	currentIndex = selectedIndex;
	radius = circle.getRadius();
	pointCount = circle.getPointCount();
	//position = circle.getPosition();
	velocity = circle.getVelocity();
	textString = circle.getString();
	ImGuiCircleFillColor = circle.getImGuiFillColor();
}

void cwt::ImGuiLoopHandler::UpdateCWT(unsigned selectedIndex, CircleWithText &circle)
{
	if (currentIndex == selectedIndex) {
		std::cout << "Updating circle with selectedIndex " << selectedIndex << std::endl;
		circle.setRadius(radius);
		if (circle.getPointCount() != pointCount) circle.setPointCount(pointCount);
		//if (circle.getPosition() != position) circle.setPosition(position);
		if (circle.getVelocity() != velocity) circle.setVelocity(velocity);
		if (circle.getString() != textString) circle.setString(textString);
		if (circle.getImGuiFillColor() != ImGuiCircleFillColor) circle.setCircleFillColor(ImGuiCircleFillColor);
		circle.isCircleDrawn = isCircleDrawn;
		circle.isTextDrawn = isTextDrawn;
	}
	//circle.move();
}

void cwt::ImGuiLoopHandler::UpdateCWT(unsigned selectedIndex, std::list<CircleWithText> &lsCircles)
{
	auto temp = getElementRef(selectedIndex, lsCircles);
	UpdateCWT(selectedIndex, getElementRef(selectedIndex, lsCircles));
}
