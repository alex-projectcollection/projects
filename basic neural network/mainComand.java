package newneural_network;

import java.util.Scanner;

public class mainComand {

	public static void main(String[] args) {
		neruron[] base1 = new neruron[21];

		neruron out1 = new neruron();

		System.out.println(
				"the neural network to deside if a string is containing more 1 then 0 or viseversa is being build ");

		network network = new network(base1, out1);

		System.out.println("enter the mumber of training examples you whant to try max number is integer max: ");
		Scanner scanner = new Scanner(System.in);
		String input = scanner.nextLine();
		int result = Integer.parseInt(input);

		while (result < 1) {
			System.out.println("enter a number higher then 1:");
			input = scanner.nextLine();
			result = Integer.parseInt(input);
		}
		network.train(result);

		int dowegoon = 0;

		while (dowegoon == 0) {

			System.out.println(
					"enter a 21 bit string of 0 and 1 to get an answare if there is more 1 or 0 for exit enter 9:");

			input = scanner.nextLine();
//			if (input != "9") {
				while (input.length() != 21) {
					System.out.println("enter the input agin");
					input = scanner.nextLine();

				}
				network.calculate(input);

				if (network.getTarget().getOut() > 0) {
					System.out.println("there are more 1 then 0");
				} else {
					System.out.println("there is more 0 then 1");
				}
//		S	}else {
//				dowegoon=1;
//			}
		}
		scanner.close();

		// printing cheak
//		for(int i=0;i<network.getBase().length;i++) {
//			System.out.println(network.getBase()[i].getS());
//		}

	}

}
