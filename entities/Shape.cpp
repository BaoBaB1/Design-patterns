#include "Shape.h"
#include "../behavioral/behavioral.h"

void Circle::visit(visitor::IShapeVisitor* visitor) const {
  visitor->visit(*this);
}

void Square::visit(visitor::IShapeVisitor* visitor) const {
  visitor->visit(*this);
}
