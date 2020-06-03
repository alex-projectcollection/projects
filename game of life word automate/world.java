package game_of_life;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class world extends JFrame implements ActionListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JPanel mainBlock;

	private int ifWeStart = 0;
	private int[][][] Database = new int[20][20][10]; // first 2 size ,3 sea or land ,3-3-5 woods city or ice,3-6-7
														// clouds
	// or polution , and 4 direction of wind
	private double random;

	private final int SIZE = 20;

	private JButton button;

	public void randomWorld() {
		for (int i = 0; i < Database.length; i++) {
			for (int j = 0; j < Database[0].length; j++) {

				random = Math.random();
				if (random > 0.5) // then land
				{
					Database[i][j][0] = 0;
					Database[i][j][1] = 1;

					if (Database[i][j][1] == 1) { // if there is land
						random = Math.random();
						if (random >= 0.9)// there is ice
						{
							Database[i][j][4] = 1;
						}
						if (random < 0.3)// there is land
						{

						}
						if (random >= 0.3 && random < 0.6)// there is woods
						{
							Database[i][j][2] = 1;

						}
						if (random >= 0.6 && random < 0.9)// there is city
						{
							Database[i][j][3] = 1;
							Database[i][j][6] = 1; // the city is poluted
						}
					}

				} else { // than sea
					Database[i][j][0] = 1;
					Database[i][j][1] = 0;
				}

				if (Database[i][j][0] == 1) { // if there is sea
					random = Math.random();
					if (random > 0.8)// ther is ice
					{
						Database[i][j][4] = 1;
					}
				}

				// clouds cover
				random = Math.random();
				if (random > 0.5) {
					Database[i][j][5] = 1;
				} else {
					Database[i][j][5] = 0;
				}

				// initial polution
				random = Math.random();
				if (random > 0.9) {
					Database[i][j][6] = 1;
				} else {
					Database[i][j][6] = 0;
				}

				// temp in c
				random = Math.random() * 50;
				Database[i][j][9] = (int) random;

				// wind direction
				random = Math.random();
				if (random < 0.15) {
					Database[i][j][7] = 1;
				} else if (random < 0.15 && random >= 0.30) {
					Database[i][j][7] = 2;
				} else if (random < 0.3 && random >= 0.45) {
					Database[i][j][7] = 3;
				} else if (random < 0.45 && random >= 0.6) {
					Database[i][j][7] = 4;
				}

				// wind entensity
				random = Math.random();
				if (random < 0.25) {
					Database[i][j][8] = 1;
				} else if (random < 0.5 && random >= 0.25) {
					Database[i][j][8] = 2;
				} else if (random < 0.75 && random >= 0.5) {
					Database[i][j][8] = 3;
				} else if (random < 1 && random >= 0.75) {
					Database[i][j][8] = 4;
				}

			}
		}
	}

	public void draw() {

//		try
//		{
//		    Thread.sleep(1000);
//		}
//		catch(InterruptedException ex)
//		{
//		    Thread.currentThread().interrupt();
//		}
		// dont tuch
		mainBlock = new JPanel();
		add(mainBlock);

		setSize(1000, 1000);

		int num_of_water=0;
		int num_of_land=0;
		int num_of_woods=0;
		int num_of_city=0;
		int num_of_ice=0;
		int num_of_cluds=0;
		int num_of_poulution=0;
		int num_of_nowind=0;
		int num_of_southhwind=0;
		int num_of_westwind=0;
		int num_of_northwind=0;
		int num_of_eastwind=0;
		
		// till here

		mainBlock.setLayout(new GridLayout(20, 20));

		for (int i = 0; i < Database.length; i++) {
			for (int j = 0; j < Database[0].length; j++) {
				JPanel block = new JPanel();
				// add sea
				if (Database[i][j][0] == 1) {
					
					block = new JCloud(Database[i][j][5], Database[i][j][6], Database[i][j][7]);
					block.setBackground(Color.BLUE);
					if(Database[i][j][0] == 1&&Database[i][j][4] ==0 ) {
						num_of_water++;
						
					}


				}
				// add ground
				if (Database[i][j][1] == 1) {

					block = new JCloud(Database[i][j][5], Database[i][j][6], Database[i][j][7]);
					block.setBackground(Color.ORANGE);

					if(Database[i][j][1] == 1&&Database[i][j][4] ==0 ) {
						num_of_land++;
						
					}

				}
				// add woods
				if (Database[i][j][2] == 1) {

					block = new JCloud(Database[i][j][5], Database[i][j][6], Database[i][j][7]);
					block.setBackground(Color.green);

					if(Database[i][j][2] == 1&&Database[i][j][4] ==0 ) {
						num_of_woods++;
						
					}


				}
				// add city
				if (Database[i][j][3] == 1) {

					block = new JCloud(Database[i][j][5], Database[i][j][6], Database[i][j][7]);
					block.setBackground(Color.GRAY);

					if(Database[i][j][3] == 1&&Database[i][j][4] ==0 ) {
						num_of_city++;
						
					}


				}
				// addd ice
				if (Database[i][j][4] == 1) {

					block = new JCloud(Database[i][j][5], Database[i][j][6], Database[i][j][7]);
					block.setBackground(Color.WHITE);

					if(Database[i][j][4] ==1 ) {
						num_of_ice++;
						
					}

				}
				
				if(Database[i][j][5] == 1 ) {
					num_of_cluds++;
					
				}
				
				if(Database[i][j][6] == 1) {
					num_of_poulution++;
					
				}
				
				if(Database[i][j][7] == 0) {
					num_of_nowind++;
					
				}
				
				if(Database[i][j][7] == 1) {
				 num_of_southhwind++;
		
					
				}
				
				if(Database[i][j][7] == 2) {
					num_of_westwind++;
					
				}
				if(Database[i][j][7] ==3) {
					num_of_northwind++;
					
				}
				if(Database[i][j][7] == 4) {
					num_of_eastwind++;
					
				}

				

				
				mainBlock.add(block);
			}
		}
		
		System.out.println("the number of sea: "+num_of_water+"\n"+
		"the number of land: "+num_of_land+"\n"+
		"the number of woods: "+ num_of_woods +"\n"+
		"the number of city: "+ num_of_city +"\n"+
		"the number of ice: "+ num_of_ice +"\n"+
		"the number of cluds: "+ num_of_cluds +"\n"+
		"the number of poulution: "+ num_of_poulution +"\n"+
		"the number of no-wind: "+ num_of_nowind +"\n"+
		"the number of south-wind: "+ num_of_southhwind +"\n"+
		"the number of west-wind: "+ num_of_westwind +"\n"+
		"the number of north-wind: "+ num_of_northwind +"\n"+
		"the number of east-wind: "+ num_of_eastwind +"\n"
);
		 num_of_water=0;
		 num_of_land=0;
		 num_of_woods=0;
		 num_of_city=0;
		 num_of_ice=0;
		 num_of_cluds=0;
		 num_of_poulution=0;
		 num_of_nowind=0;
		 num_of_southhwind=0;
		 num_of_westwind=0;
		 num_of_northwind=0;
		 num_of_eastwind=0;

	}

	public world() {

		super("world");

		button = new JButton("next day");
		add(button, BorderLayout.SOUTH);

		button.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {

				// dont tuch again
				mainBlock.repaint();

				mainBlock.removeAll();

				setSize(1050, 1050);

				// antil here

				int[][][] tempDatabase = new int[20][20][10];
				tempDatabase = Database;

				for (int i = 0; i < Database.length; i++) {
					for (int j = 0; j < Database[0].length; j++) {

						// if city the there is pulotion there;

						if (Database[i][j][3] == 1) {
							tempDatabase[i][j][6] = 1;
						}
						// if forest then no polutiion

						if (Database[i][j][2] == 1) {
							tempDatabase[i][j][6] = 0;
						}

						// if sea then cloud formation
						if (Database[i][j][0] == 1) {
							random = Math.random();

							if (random > 0.7) {
								tempDatabase[i][j][5] = 1;

							}
						}

						// if cluds then wind moves them and too much make rain
						if (Database[i][j][5] == 1) {
							int count = 0;
//							for (int soraundingi = 0; soraundingi <= 7; soraundingi++) {
							// corners 1
							if (i == 0 && j == 0) {
								if (Database[19][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[1][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[19][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[19][1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
//2
							} else if (i == 19 && j == 0) {

								if (Database[i - 1][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
//3
							} else if (i == 0 && j == 19) {

								if (Database[19][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[19][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[19][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[1][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								// 4
							} else if (i == 19 && j == 19) {

								if (Database[0][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								// top raw
							} else if (j == 0) {

								if (Database[i - 1][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][19][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								// botem rwa
							} else if (j == 19) {

								if (Database[i - 1][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][0][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								// left raw
							} else if (i == 0) {

								if (Database[19][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[19][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[19][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								// right raw
							} else if (i == 19) {

								if (Database[0][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[0][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
							} else {

								if (Database[i - 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j - 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i - 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
								if (Database[i + 1][j + 1][5] == 1) {
									count++;
//										soraundingi++;
								}
							}
							// if to much cluds then rain
							if (count > 5) {
								tempDatabase[i][j][5] = 0;

//									
//									
//									// if rain then forest or ice can grow
//									// woods grow
								if (Database[i][j][2] == 1) {
									random = Math.random();
									// then new forest
									if (random > 0.7) {

										// if a dgust grund
										if (i > 0 && i < 19 && j > 0 && j < 19) {

											if (Database[i][j - 1][1] == 1 && Database[i][j - 1][2] == 0) {
												tempDatabase[i][j - 1][2] = 1;

											} else if (Database[i - 1][j][1] == 1 && Database[i - 1][j][2] == 0) {
												tempDatabase[i - 1][j][2] = 1;

											} else if (Database[i + 1][j][1] == 1 && Database[i + 1][j][2] == 0) {
												tempDatabase[i + 1][j][2] = 1;

											} else if (Database[i][j + 1][1] == 1 && Database[i][j + 1][2] == 0) {
												tempDatabase[i][j + 1][2] = 1;

											}
										}
									}
								}
//									// ice grow
								if (Database[i][j][4] == 1) {
									random = Math.random();
									// then new ice
									if (random > 0.7) {

										// if a dgust grund

										if (i > 0 && i < 19 && j > 0 && j < 19) {

											if (Database[i][j - 1][4] == 0) {
												tempDatabase[i][j - 1][4] = 1;

											} else if (Database[i - 1][j][4] == 0) {
												tempDatabase[i - 1][j][4] = 1;

											} else if (Database[i + 1][j][4] == 0) {
												tempDatabase[i + 1][j][4] = 1;

											} else if (Database[i][j + 1][4] == 0) {
												tempDatabase[i][j + 1][4] = 1;

											}
										}
									}
								}

								// rain end

							}

//							}

							// end clouds
						}

						// till here all works rain works forests and ice grows

						// wind moves clouds and pulotion
						if (Database[i][j][7] > 0 && (Database[i][j][5] == 1 || Database[i][j][6] == 1)) {
							if (i > 0 && i < 19 && j > 0 && j < 19) {
//
								// south wind
								if (Database[i][j][7] == 1) {
									// moves clud
									if (Database[i][j][5] == 1) {
										tempDatabase[i][j][5] = 0;
										tempDatabase[i + 1][j][5] = 1;
										// moves polution
									}
									if (Database[i][j][6] == 1) {
										tempDatabase[i][j][6] = 0;
										tempDatabase[i + 1][j][6] = 1;
									}

								}
								// wind to the west
								if (Database[i][j][7] == 2) {
									// moves clud
									if (Database[i][j][5] == 1) {
										tempDatabase[i][j][5] = 0;
										tempDatabase[i][j - 1][5] = 1;
										// moves polution
									}
									if (Database[i][j][6] == 1) {
										tempDatabase[i][j][6] = 0;
										tempDatabase[i][j - 1][6] = 1;
									}

								}
								// wind to the north
								if (Database[i][j][7] == 3) {
									// moves clud
									if (Database[i][j][5] == 1) {
										tempDatabase[i][j][5] = 0;
										tempDatabase[i - 1][j][5] = 1;
										// moves polution
									}
									if (Database[i][j][6] == 1) {
										tempDatabase[i][j][6] = 0;
										tempDatabase[i - 1][j][6] = 1;
									}

								}
								// wind to the east
								if (Database[i][j][7] == 4) {
									// moves clud
									if (Database[i][j][5] == 1) {
										tempDatabase[i][j][5] = 0;
										tempDatabase[i][j][5] = 1;
										// moves polution
									}
									if (Database[i][j][6] == 1) {
										tempDatabase[i][j][6] = 0;
										tempDatabase[i][j + 1][6] = 1;
									}

								}
//								
//
							}
						}
//						

						// gam oved
						// poulution destroyiys ice
						if (Database[i][j][6] == 1) {
							if (Database[i][j][4] == 1) {
								random = Math.random();
								if (random > 0.5) {
									tempDatabase[i][j][4] = 0;
								}
							}
						}

						// looks like it all workes till here

						// random wind generation
						random = Math.random();

						if (random > 0.6) {
							if (random > 0.6 && random <= 0.7) {
								tempDatabase[i][j][7] = 1;
							} else if (random > 0.7 && random <= 0.8) {
								tempDatabase[i][j][7] = 2;
							} else if (random > 0.8 && random <= 0.9) {
								tempDatabase[i][j][7] = 3;
							} else if (random > 0.9 && random <= 1) {
								tempDatabase[i][j][7] = 4;
							}
						} else {
							tempDatabase[i][j][7] = 0;
						}

						// nishar letakem bagim v ltehnet rohach annom sabba v rojach amur kvar laziz
						// zihom v ananim
						// hamshe po odd hokay mavar pooooo...

					}
				}
				Database = tempDatabase;

				draw();

			}

		});

		if (ifWeStart == 0) {
			ifWeStart++;
			randomWorld();
			draw();

			setSize(1000, 1000);
			setVisible(true);
		}

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}

}
