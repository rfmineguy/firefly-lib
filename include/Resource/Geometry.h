#ifndef FL_RES_GEOMETRY_H
#define FL_RES_GEOMETRY_H

typedef struct _Geometry Geometry;

void BindGeometry(Geometry*);
void UnbindGeometry();
void FreeGeometry(Geometry*);

void PopulateQuad(Geometry*);

#endif
