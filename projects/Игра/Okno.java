package Game;

import java.awt.Container;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Okno extends JFrame{
	int slogn;
	MyPanel panel;
	int height = 380;
	int width = 596;
	
	class MyKey extends KeyAdapter{
		@Override
		public void keyPressed(KeyEvent e) {
			int key = e.getKeyCode();
			if(key==39) {
				panel.x+=30;
				if(panel.x > width*0.9)
				{
					panel.x = 0;
				}
			}
			if(key==37) {
				panel.x-=30;
				if(panel.x < -width*0.2)
				{
					panel.x = (int)(width * 0.85);
				}
			}
			
		}
	}
	
	public Okno(int s) throws IOException {
		addKeyListener(new MyKey());
		setBounds(200,200,width,height);
		setTitle("Моя игра");
		
		Container c = getContentPane();
		panel = new MyPanel(s);
		c.add(panel);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);

	}
}

