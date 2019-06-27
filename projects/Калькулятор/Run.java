
import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;



public class Run extends JFrame {
	private JTextArea text;
	
	private double number1=0,number2=0;
	private int oper=0;
	
	
	/**
	 * 
	 */
	public Run() {
		
		
		JMenuBar menuBar = new JMenuBar();
		JMenu file = new JMenu("Файл");
		JMenu vid = new JMenu("Вид");
		JMenu spravka = new JMenu("Справка");
		JMenuItem sprav = new JMenuItem("Вызов справки");
		
		spravka.add(sprav);
		
		Font f = new Font("Verdana",Font.BOLD,16);
		file.setFont(f);
		vid.setFont(f);
		spravka.setFont(f);
		JMenu myMenu = new JMenu("Кнопки");
		vid.add(myMenu);
		
		JMenuItem bw = new JMenuItem("Синий+белый");
		bw.setFont(f);
		myMenu.add(bw);
		
		JMenuItem gg = new JMenuItem("Серый+зеленый");
		gg.setFont(f);
		myMenu.add(gg);
		
		file.addSeparator();
		
		JMenuItem exit = new JMenuItem("EXIT");
		exit.setFont(f);
		file.add(exit);
		
		menuBar.add(file);
		menuBar.add(vid);
		menuBar.add(spravka);
		setJMenuBar(menuBar);
		pack();
		
		exit.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
				
			}
		});
		
		
		
		
		setLocationRelativeTo(null);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		JPanel panel = new JPanel();
		panel.setLayout(null);
		
		
		
	
		
		sprav.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				
				
				JFrame frame = new JFrame("Справка");
				frame.getContentPane();
				JLabel lab = new JLabel("Текст справки");
				frame.add(lab);
				frame.setSize(400,400);
				frame.setVisible(true);
				
			}
		});
		
		JButton[] btn = new JButton[18];
		Font btnFont = new Font("serif",Font.ITALIC,15);
		
		bw.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				for(int i=0; i<18; i++) {
					btn[i].setBackground(Color.blue);
					btn[i].setForeground(Color.white);
				}
				
			}
			
		});
		
		
		gg.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				for(int i=0; i<18; i++) {
					btn[i].setBackground(Color.gray);
					btn[i].setForeground(Color.green);
				}
			}
		});
		
		
		for(int i=0;i<18;i++) {
			btn[i] = new JButton();
			
			
			
			btn[i].addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					JButton btn = (JButton) e.getSource();
					String str = btn.getText().trim();
					//System.out.println(str);
					if(str.equals("Выход")) {
						System.exit(0);
					}
					
					else if(str.equals("C")) {
						text.setText("");
						number1=0;
						number2=0;
					}
					else if(str.contentEquals("sqrt")) {
						number1 = Double.parseDouble(text.getText());
						text.setText(""+Math.sqrt(number1));
					}
					
					
					
					else if(str.equals("=")) {
						number2 = Double.parseDouble(text.getText());
						if(oper==1) {
							text.setText(""+(number1+number2));
						}
						else if(oper==2) {
							text.setText(""+(number1-number2));
						}
						if(oper==3) {
							text.setText(""+(number1*number2));
						}
						if(oper==4) {
							text.setText(""+(number1/number2));
						}
						if(oper==5) {
							text.setText(""+Math.sqrt(number1));
						}
						
					}
					else if(str.equals("+")) {
						oper=1;
						number1 = Double.parseDouble(text.getText());
						text.setText("");
					}
					else if(str.equals("-")) {
						oper=2;
						number1 = Double.parseDouble(text.getText());
						text.setText("");
					}
					else if(str.equals("*")) {
						oper=3;
						number1 = Double.parseDouble(text.getText());
						text.setText("");
					}
					else if(str.equals("/")) {
						oper=4;
						number1 = Double.parseDouble(text.getText());
						if(number1==0) {
							try {
								throw new Exception("На ноль делить нельзя!");
							} catch (Exception e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						}
						text.setText("");
					}
					
					
					else {
						text.setText(str);
					}
					
				}
			});
			
			panel.add(btn[i]);
		}
		
		
		for(int i=0;i<9;i++) {
			btn[i].setText(" "+(i+1));
		}
		btn[9].setText(" "+0);
		btn[10].setText("+");
		btn[11].setText("-");
		btn[12].setText("*");
		btn[13].setText("/");
		btn[14].setText("=");
		btn[15].setText("C");
		btn[16].setText("Выход");
		btn[17].setText("sqrt");
		
		for(int i=0; i<18; i++) {
			btn[i].setFont(btnFont);
			int cols = i % 3;
			int rows = i / 3;
			btn[i].setLocation(100 + cols * 110, 50+30*rows);
			btn[i].setSize(100,25);
			btn[i].setBackground(Color.blue);
			btn[i].setForeground(Color.white);
		}
		
		JLabel res = new JLabel("Результат");
		res.setFont(new Font("serif",Font.ITALIC,30));
		res.setBounds(130, 0,300,50);
		panel.add(res);
		
		text = new JTextArea();
		text.setFont(new Font("arial",Font.BOLD,30));
		text.setForeground(Color.red);
		text.setBounds(300,10,300,35);
		panel.add(text);
		
		
		
		c.add(panel);
		
						
		setSize(800,600);
		setTitle("Калькулятор версия 1.0");
		setVisible(true);
	}
}
