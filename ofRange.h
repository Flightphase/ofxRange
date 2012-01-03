/*
 *  ofRange.h
 *  SFEditor
 *
 *  Created by Jim on 1/15/11.
 *
 */

//----------------------------------------------------------
// ofRange
//----------------------------------------------------------
#pragma once

class ofRange {
  public:
	virtual ~ofRange(){}
	
	ofRange( const ofRange& rg){
		min = rg.min;
		max = rg.max;
	}
	
	ofRange( float _min=0.0f, float _max=1.0f){
		min = _min;
		max = _max;
	}
	
	void set(float _min, float _max){
		min = _min;
		max = _max;
	}
	
	void setMin(float _min){
		min = MIN(_min, max);
	}
	
	void setMax(float _max){
		max = MAX(min, _max);
	}
	
    bool operator==( const ofRange& rg ) {
        return (min == rg.min) && (max == rg.max);
    }
	
    bool operator!=( const ofRange& rg ) {
        return (min != rg.min) || (max != rg.max);
    }
	
	bool contains(float p){
		return p >= min && p < max;
	}
	
	bool contains(const ofRange& rg){
		return rg.min >= min && rg.max < max;
	}
	
	bool intersects(const ofRange& rg){
		return contains(rg.min) || contains(rg.max);
	}

	ofRange getClamped(const ofRange& rg){
		return contains(rg.min) || contains(rg.max);
	}
	
	float span(){
		return max - min;
	}
	
	ofRange getClamped(const ofRange& rg) const {
		ofRange crg;
		crg.min = MAX(rg.min,min);
		crg.max = MIN(rg.max,max);		
		return crg;
	}
	
    ofRange& clamp(const ofRange& rg){
		min = MAX(rg.min,min);
		max = MIN(rg.max,max);
		return *this;
	}

	//union
	ofRange operator+( const ofRange& rg ) const;
	ofRange& operator+=( const ofRange& rg );
	//intersection
	ofRange operator-(const ofRange& rg) const;
	ofRange& operator-=(const ofRange& rg);

	
	ofRange operator+( const float f ) const;
	ofRange& operator+=( const float f );
	ofRange operator-( const float f) const;
	ofRange& operator-=(const float f);
	
	
	friend ostream& operator<<(ostream& os, const ofRange& rg);
	friend istream& operator>>(istream& is, const ofRange& rg);

    union  {
        struct {
            float min;
            float max;
        };
        float r[2];
    };	
};

//ofVec2f

//non member ops
ofRange operator+( float f, const ofRange& vec );
ofRange operator-( float f, const ofRange& vec );

inline ofRange ofRange::operator+( const ofRange& rg ) const {
	return ofRange(MIN(min, rg.min), MAX(max, rg.max));
}

inline ofRange& ofRange::operator+=( const ofRange& rg ){
	min = MIN(min, rg.min);
	max = MAX(max, rg.max);
	return *this;
}

inline ofRange ofRange::operator-( const ofRange& rg) const {
//	if(!ofRange::intersects(rg)) return ofRange(0,0);
	return ofRange(MAX(min, rg.min), MIN(max, rg.max));
}

inline ofRange& ofRange::operator-=( const ofRange& rg ) {
//	if(!ofRange::intersects(rg)) return ofRange(0,0);
	min = MAX(min, rg.min);
	max = MIN(max, rg.max);
	return *this;
}

inline ofRange ofRange::operator+( const float f ) const{
	return ofRange(min+f, max+f);
}

inline ofRange& ofRange::operator+=( const float f ){
	min += f;
	max += f;
	return *this;
}

inline ofRange ofRange::operator-( const float f) const{
	return ofRange(min-f, max-f);
}

inline ofRange& ofRange::operator-=(const float f) {
	min -= f;
	max -= f;
	return *this;
}

inline ostream& operator<<(ostream& os, const ofRange& rg) {
	os << "[" << rg.min << " - " << rg.max << "]";
	return os;
}

inline istream& operator>>(istream& is, ofRange& rg) {
	is.ignore(1);
	is >> rg.min;
	is.ignore(3);
	is >> rg.max;
	is.ignore(1);
	return is;
}

inline ofRange operator+( float f, const ofRange& rg ){
	return ofRange(f + rg.min, f + rg.max);
}

inline ofRange operator-( float f, const ofRange& rg ){
	return ofRange(f - rg.min, f - rg.max);
};


