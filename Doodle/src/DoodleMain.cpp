#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct point
{
	int x, y;
	double moving;
};

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(400, 533), "Doodle Game!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3;
	t1.loadFromFile("images/background.png");
	t2.loadFromFile("images/platform.png");
	t3.loadFromFile("images/doodle.png");

	Sprite sBackground(t1), sPlat(t2), sPers(t3);
	int platNum = 18;
	point* plat = new point[platNum];

	int windowHeight = 533;
	int windowWidth = 400;

	for (int i = 0; i < platNum / 2; i++) // ramdom to show 10 platforms
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}
	for (int i = platNum / 2; i < platNum - 5; i++) // ����@�Ǧb�ݤ��쪺�a��
	{
		plat[i].x = rand() % 400;
		plat[i].y = -rand() % 533;
	}
	for (int i = platNum - 5; i < platNum; i++) // ����@�Ǧb�ݤ��쪺�a��
	{
		plat[i].x = rand() % 400;
		plat[i].y = 533 - rand() % (533 * 2);
		if (plat[i].y % 2 == 0) plat[i].moving = -2 - rand() % 20/10;
		else plat[i].moving = 2 + rand() % 20/10;
	}

	// (0, 0)�O���W��
	int x = 100, y = 100, h = 200; // (x, y) initial ���� position // h �O�p�����̪�i�H��window bar�h��, �{���X�b�U��if (y < h)
	float dx = 0, dy = 0;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		dy += 0.3; // �j���O�������O��g(�j��)
		y += dy;
//		y -= 3; // �p�G�Q�n�p������������۹�B�ʴN�O�o��

		if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
		if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

		if (x >= windowWidth) // when move out of left bound
			x -= (windowWidth);
		if (x <= 0) // when move out of right bound
			x += (windowWidth);

		if (y > 500) // ��¼¼�F �ڤ����D������L�g500
			dy = -20; // When player die -20 is jump upward. If +20 is falling to the hell;

		if (y < h) // �p�����P�e�������� ������window bar�n���ӶZ��h
			for (int i = 0; i < platNum; i++) // to create platform when needing
			{
				y = h;
				plat[i].y = plat[i].y - dy;
				if (plat[i].y > 533)//533�O�U��
				{
//					plat[i].y = 0; //�o�쥻�@�̼g��
					plat[i].y = -(rand() % 533);
					plat[i].x = rand() % 400;
				}
			}

		for (int i = platNum - 5; i < platNum; i++) // ����@�Ǧb�ݤ��쪺�a��
		{
			plat[i].x += plat[i].moving;
			if (plat[i].x >= windowWidth || plat[i].x <= 0) // when move out of left bound
				plat[i].moving *= (-1);
		}

		for (int i = 0; i < platNum; i++)
			if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) &&
				(y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
			{
				dy = -10; // when you collide with platform, you will jump!
			}

		// �����x�|���p�B�ͤU�ӱ�
		for (int i = 0; i < platNum; i++)
			plat[i].y += 3;

		sPers.setPosition(x, y);

		app.draw(sBackground);
		app.draw(sPers);
		for (int i = 0; i < platNum; i++)
		{
			sPlat.setPosition(plat[i].x, plat[i].y);
			app.draw(sPlat);	
		}

		app.display();
	}
	return 0;
}
