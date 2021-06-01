#ifndef TILE
#define TILE

namespace tilegames{
	class Tile{
		char gfx;
		int flags;
	public:
		Tile(char c = '}', int flg = 0):gfx(c),flags(flg){}
		Tile(const Tile& base) : gfx(base.gfx), flags(base.flags){}
		const char GFX() const{return gfx;}
		///Get or set
		int& Flags() {return flags;}
		virtual ~Tile(){}
	};
}
#endif

