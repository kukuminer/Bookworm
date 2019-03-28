#ifndef _GRAPHIC_H
#define _GRAPHIC_H


class graphic {
  public:
    graphic();

    void setPosition(int x, int y);

    virtual void draw(sf::RenderWindow & win);

    int getX();

    int getY();

    virtual ~graphic();


  protected:
    sf::RectangleShape obj;

};
#endif
