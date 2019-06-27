package Game;

import java.awt.Container;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class Game {
	public static  void start() throws IOException{
		String res = JOptionPane.showInputDialog("Выберите сложность игры");
		int slogn = Integer.parseInt(res);
		if(slogn>=1 && slogn<=6) {
			new Okno(slogn);
		}
		else {
			 JOptionPane.showMessageDialog(null,"Некорректный ввод сложности");
		}
	}
	

	public static void main(String[] args) throws IOException {
		
		 start();

	}

}
