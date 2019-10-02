package ex1;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JTextArea;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Ex1 {

	private JFrame frame;
	private JTextArea textArea;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Ex1 window = new Ex1();
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
	public Ex1() {
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
		
		JButton btnClickMe = new JButton("Click Me");
		btnClickMe.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.append("Click!");
			}
		});
		panel.add(btnClickMe);
		
		JButton btnPushMe = new JButton("Push Me");
		btnPushMe.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.append("Push!");
			}
		});
		panel.add(btnPushMe);
		
		JButton btnTapMe = new JButton("Tap Me");
		btnTapMe.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.append("Tap!");
			}
		});
		panel.add(btnTapMe);
		
		textArea = new JTextArea();
		frame.getContentPane().add(textArea, BorderLayout.CENTER);
	}

}
