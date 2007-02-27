/*****
 * drawlabel.h
 * John Bowman 2003/03/14
 *
 * Add a label to a picture.
 *****/

#ifndef DRAWLABEL_H
#define DRAWLABEL_H

#include "drawelement.h"
#include "path.h"
#include "angle.h"
#include "transform.h"

namespace camp {
  
class drawLabel : public virtual drawElement {
protected:
  mem::string label,size;
  transform T;		// A linear (shiftless) transformation.
  pair position;
  pair align;
  pair scale;
  pen pentype;
  double width,height,depth;
  bool havebounds;
  bool suppress;
  pair Align;
  pair texAlign;
  bbox Box;
  
public:
  drawLabel(mem::string label, mem::string size, transform T, pair position,
	    pair align, pen pentype)
    : label(label), size(size), T(shiftless(T)), position(position),
      align(align), pentype(pentype), width(0.0), height(0.0), depth(0.0),
      havebounds(false), suppress(false) {} 
  
  virtual ~drawLabel() {}

  void getbounds(iopipestream& tex, const mem::string& texengine);
  
  void checkbounds();
    
  void bounds(bbox& b, iopipestream&, boxvector&, bboxlist&);
  
  bool texbounds(iopipestream& tex, mem::string& s, bool warn,
		 const char **abort);
    
  bool islabel() {
    return true;
  }

  bool write(texfile *out);

  drawElement *transformed(const transform& t);
  
  void labelwarning(const char *action); 
};

class drawLabelPath : public drawLabel, public drawPathPenBase {
private:  
  mem::string justify;
  pair shift;
public:
  drawLabelPath(mem::string label, mem::string size, path src,
		mem::string justify, pair shift, pen pentype) : 
    drawLabel(label,size,identity(),pair(0.0,0.0),align,pentype),
    drawPathPenBase(src,pentype), justify(justify), shift(shift) {}
  
  virtual ~drawLabelPath() {}

  void bounds(bbox& b, iopipestream& tex, boxvector&, bboxlist&);
  
  bool write(texfile *out);
  
  drawElement *transformed(const transform& t);
};

}

#endif
