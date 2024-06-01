bool sign(float x1, float y1, float x2, float y2, float x3, float y3) {
    return ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) > 0;
}

bool isPointInTriangle(double c1, double c2, double x1, double y1, double x2, double y2, double x3, double y3){
    bool s1 = sign(c1, c2, x1, y1, x2, y2);
    bool s2 = sign(c1, c2, x2, y2, x3, y3);
    bool s3 = sign(c1, c2, x3, y3, x1, y1);
    return (s1 & s2 & s3) || !(s1 | s2 | s3);
}

double dis(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double distanceFromPointToLine(double x1, double y1, double x2, double y2, double x3, double y3){
    double midx = (x2 + x3) / 2.0;
    double midy = (y2 + y3) / 2.0;

    return dis(x1, x2, midx, midy);
}

bool isCircleInTriangle(double c1, double c2, double radius, double x1, double y1, double x2, double y2, double x3, double y3){
    bool ret = isPointInTriangle(c1, c2, x1, y1, x2, y2, x3, y3);
    ret &= ((distanceFromPointToLine(c1, c2, x1, y1, x2, y2)) < radius);
    ret &= ((distanceFromPointToLine(c1, c2, x2, y2, x3, y3)) < radius);
    ret &= ((distanceFromPointToLine(c1, c2, x3, y3, x1, y1)) < radius);

    return ret;
}

typedef struct point
{
    int x, y;
}point;



point findPointInTriangle(double c1, double c2, double radius, double x1, double y1, double x2, double y2, double x3, double y3){
    point ret = {0,0};
    double lx = (x1 + x2 + x3) / 3.0, ly = (y1 + y2 + y3) / 3.0;
    double rx = c1, ry = c2;

    while(dis(lx, ly, rx, ry) > 1e-4){
        double midx = (lx + ly) / 2.0, midy = (rx + ry) / 2.0;
        if(isCircleInTriangle(midx, midy, x1, y1, x2, y2, x3, y3)){
            ret.x = midx, ret.y = midy;
            lx = midx, ly = midy;
        }else{
            rx = midx, ry = midy;
        }
    }

    return ret;
}