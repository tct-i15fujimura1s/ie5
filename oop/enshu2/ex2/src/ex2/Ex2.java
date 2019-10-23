package ex2;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Ex2 {

	private JFrame frame;
	private JPanel panel_1;
  private Random rand = new Random();

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Ex2 window = new Ex2();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Ex2() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.NORTH);

		JButton btnRed = new JButton("Red");
		btnRed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				panel_1.setBackground(Color.RED);
			}
		});
		btnRed.setForeground(Color.RED);
		panel.add(btnRed);

		JButton btnBlue = new JButton("Blue");
		btnBlue.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				panel_1.setBackground(Color.BLUE);
			}
		});
		btnBlue.setForeground(Color.BLUE);
		panel.add(btnBlue);

		JButton btnGreen = new JButton("Green");
		btnGreen.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				panel_1.setBackground(Color.GREEN);
			}
		});
		btnGreen.setForeground(Color.GREEN);
		panel.add(btnGreen);

		JButton btnTurquoise = new JButton("Turquoise");
		btnTurquoise.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				panel_1.setBackground(btnTurquoise.getForeground());
			}
		});
		btnTurquoise.setForeground(new Color(0, 157, 191));
		panel.add(btnTurquoise);

    JButton btnRandom = new JButton("Random");
    btnRandom.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
        int r, g, b;
        int x = rand.nextInt(255), y = rand.nextInt(255);
        switch(rand.nextInt(3)) {
          case 0: r = 255; g = x; b = y; break;
          case 1: r = x; g = 255; b = y; break;
          default: r = x; g = y; b = 255;
        }
				panel_1.setBackground(new Color(r, g, b));
			}
		});
    panel.add(btnRandom);


		panel_1 = new JPanel();
		panel_1.setBackground(Color.ORANGE);
		frame.getContentPane().add(panel_1, BorderLayout.CENTER);
	}

}
