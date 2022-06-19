#include "BERect.h"

BERect::BERect()
    : x(0.f), y(0.f), width(0.f), height(0.f)
{}
BERect::BERect(BEVector2 origin, BEVector2 size)
    : x(origin.x), y(origin.y), width(size.x), height(size.y)
{}
BERect::BERect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height)
{}

bool BERect::Intersect(const BERect& r) const
{
    BEVector2 rb = RightBottom();
    BEVector2 rb2 = r.RightBottom();
    return x <= rb2.x && r.x <= rb.x && y <= rb2.y && r.y <= rb.y;
}
bool BERect::IsInside(const BERect& r) const
{
    return x <= r.x && y <= r.y && width >= r.width && height >= r.height;
}
bool BERect::IsInside(const BEVector2& p) const
{
    BEVector2 rb = RightBottom();
    return x <= p.x && y <= p.y && rb.x >= p.x && rb.y >= p.y;
}

BEVector2 BERect::LeftTop() const
{
    return { x, y };
}
BEVector2 BERect::RightTop() const
{
    return { x + width, y };
}
BEVector2 BERect::LeftBottom() const
{
    return { x, y + height };
}
BEVector2 BERect::RightBottom() const
{
    return { x + width, y + height };
}