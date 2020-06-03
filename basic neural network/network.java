package newneural_network;

public class network {

	private neruron[] base = new neruron[21];

	private double[] arcs = new double[21];

	private neruron target = new neruron();

	private double treshold = 0;

	// constractor
	public network(neruron[] base, neruron target) {
		this.base = base;
		this.target = target;
		for (int i = 0; i < base.length; i++) {
			base[i] = new neruron();
			arcs[i] = 0;
		}
	}

	// geeters and setters
	public neruron[] getBase() {
		return base;
	}

	public void setBase(neruron[] base) {
		this.base = base;
	}

	public neruron getTarget() {
		return target;
	}

	public void setTarget(neruron target) {
		this.target = target;
	}

	// training the network a set number of times
	public void train(int how_much) {
		// num of times

		int miss = 0;

		for (int i = 0; i < how_much; i++) {
			int num_of1 = 0;
			String str = "";
			// generating a ranom string
			for (int j = 0; j < base.length; j++) {
				double rand = Math.random();
				if (rand < 0.5) {
					str = str + "1";
					base[j].setS('1');
					base[j].setOut(1);
					num_of1++;
				} else {
					str = str + "0";
					base[j].setS('0');
					base[j].setOut(0);

				}

			}

			// what the output needs to bee
			if (num_of1 > 10) {
				target.setOut(1);
			} else {
				target.setOut(0);
			}

			// print before lerning
			System.out.print("the treshold befor the lerning stage is: ");
			System.out.println(Double.toString(treshold));
			System.out.print("the arcs before the lerning stage are");
			for (int b = 0; b < arcs.length; b++) {
				System.out.print("-(" + arcs[b] + ")-");
			}
			System.out.println("end of arcs");

			// prosecccing on the random string
			
			//ipus aitzia
			target.setIn(0);

			for (int r = 0; r < base.length; r++) {
				target.setIn(target.getIn() + arcs[r] * (base[r].getOut()));
			}

			target.setIn(target.getIn() - treshold);
			// if we under the threshold
			//can bee bugs here

			if (target.getIn() <= 0) {
				if (num_of1 < 11) {
					for (int a = 0; a < arcs.length; a++) {
						arcs[a] = arcs[a] + base[a].getOut();
					}
					treshold = treshold - 1;
					miss++;
				}

				// if we over the treshold
			}
			if (target.getIn() > 0) {
				if (num_of1 > 11) {
					for (int a = 0; a < arcs.length; a++) {
						arcs[a] = arcs[a] - base[a].getOut();
					}
					treshold = treshold + 1;
					miss++;
				}

			}

			// conrinue here what to do with arcs

			// printng cheak
//			for(int k=0;k<getBase().length;k++) {
////				System.out.println(getBase()[k].getS());
//
//
//			}

			// printing afther lerning
			System.out.print("the lerning string is: ");

			System.out.println(str);

			System.out.print("the threshold of the outpout nuron afther the lerning is:");

			System.out.println(Double.toString(treshold));

			System.out.print("the arcs afther the lerning are: ");

			for (int b = 0; b < arcs.length; b++) {
				System.out.print("-(" + arcs[b] + ")-");
			}
			System.out.println("end of arcs");

			System.out.println("next round");
		}

		double prassenteg = 100 - 100 * ((double) miss / (double) how_much);
		System.out.println("pracenteg of perfect runs out of the total on the semple set " + prassenteg + "%");

	}

	public void calculate(String user_input) {
		char[] cArray =  user_input.toCharArray();
		
		for(int len=0;len<user_input.length();len++) {
			base[len].setS(cArray[len]);
		
			double d = (double) (cArray[len] - '0');  
			base[len].setOut(d);
			
		}
		//ipus aitzia
		target.setIn(0);
		
		for (int r = 0; r < base.length; r++) {
			target.setIn(target.getIn() + arcs[r] * (base[r].getOut()));
		}

		target.setIn(target.getIn() - treshold);
		
		
		// can bee bugs here
		if(target.getIn()<0) {
			target.setOut(1);
		}else {target.setOut(0);}
	
	}

}
