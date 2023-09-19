#pragma once
class Color {
public:
	static const Color nullColor;


	Color(int r, int g, int b);
	Color();
	inline int getRed() const {
		return red;
	}
	inline int getGreen() const {
		return green;
	}
	inline int getBlue() const {
		return blue;
	}
	inline void setRed(int r) {
		red = r;
	}
	inline void setGreen(int g) {
		green = g;
	}
	inline void setBlue(int b) {
		blue = b;
	}
	inline unsigned int getCode() {
		return (red << 24) | (green << 16) | (blue << 8);
	}
	inline void setForCode(unsigned int code) {
		red = (code & 0xFF000000u) >> 24;
		green = (code & 0xFF0000u) >> 16;
		blue = (code & 0xFF00u) >> 8;
	}

	inline bool equals(const Color& other) const {
		return (red == other.red) && (green == other.green) && (blue == other.blue); 
	}


	Color darken(int amount) const;
	Color lighten(int amount) const;
	Color averageWith(const Color& other) const;
	Color averageWith(const Color& other1, const Color& other2, const Color& other3) const;
	Color randomlyChange(int maxAmount) const;

private:
	void init(int r, int g, int b);
	int red;
	int green;
	int blue;
	
};

