
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.Scanner;
import java.text.DecimalFormat;


public class Calculator {

	public static void main(String[] args) throws Exception {
		System.out.println("Please enter the correct formula(Negative numbers must be in parentheses),Or enter 'Q' to end program");
		Calculator app = new Calculator();
		String str = null;
		Scanner s = new Scanner(System.in);
		str = s.next(); 
		while (str != "Q") {
			System.out.println("Result is: " + app.eval(str));
			str = s.next();
			if (str == "Q")
				break;
		}
		System.exit(0);
	}
	public String eval(String exp) throws Exception {
		// 转化成后缀表达式
		List list = infixExpToPostExp(exp);
		return doEval(list);
	}

	private String doEval(List list) throws Exception {
		Stack stack = new Stack();
		String element;
		double n1, n2, result;
		try {
			for (int i = 0; i < list.size(); i++) {
				element = list.get(i).toString();
				if (isOperator(element)) {
					n1 = Double.parseDouble(stack.pop() + "");
					n2 = Double.parseDouble(stack.pop() + "");
					// System.out.println("数字为：");
					// System.out.println(n1);
					// System.out.println(n2);
					result = doOperate(n2, n1, element);
					stack.push(result + "");
				} else {
					stack.push(element);
				}
			}
			return "" + stack.pop();
		} catch (RuntimeException e) {
			throw new Exception(e.getMessage());
		}
	}

	private double doOperate(double n1, double n2, String operator) {
		if (operator.equals("+"))
			return n1 + n2;
		else if (operator.equals("-"))
			return n1 - n2;
		else if (operator.equals("*"))
			return n1 * n2;
		else
			return n1 / n2;
	}

	private boolean isOperator(String str) {
		return str.equals("+") || str.equals("-") || str.equals("*")
				|| str.equals("/");
	}
	// 将中缀表达式转化成为后缀表达式
	private List infixExpToPostExp(String exp) throws Exception {
		// 字符串最后加上#作为结束符方便操作
		exp = exp + "#";
		List postExp = new ArrayList();
		StringBuffer numBuffer = new StringBuffer();
		Stack opStack = new Stack();
		char ch;
		String preChar;
		char preCh;
		opStack.push("#");
		try {
			for (int i = 0; i < exp.length();) {
				ch = exp.charAt(i);
				if (i > 0) {
					preCh = exp.charAt(i-1);
				} else {
					preCh = '0';
				}
				switch (ch) {
				case '+':
				case '-':
					if (!Character.isDigit(preCh) && preCh != ')') {
						numBuffer.append(ch);
						ch = exp.charAt(++i);
						if (Character.isDigit(ch) || ch == '.') {
							while (Character.isDigit(ch) || ch == '.') {
								numBuffer.append(ch);
								ch = exp.charAt(++i);
							}
							postExp.add(numBuffer.toString());
							numBuffer = new StringBuffer();
						} else {
							throw new Exception("illegal operator");
						}
						break;
					}
				case '*':
				case '/':
					preChar = opStack.peek().toString();
					while (priority(preChar.charAt(0)) >= priority(ch)) {
						postExp.add("" + preChar);
						opStack.pop();
						preChar = opStack.peek().toString();
					}
					opStack.push("" + ch);
					i++;
					break;
				case '(':
					opStack.push("" + ch);
					i++;
					break;
				case ')':
					String c = opStack.pop().toString();
					while (c.charAt(0) != '(') {
						postExp.add("" + c);
						c = opStack.pop().toString();
					}
					i++;
					break;
				case '#':
					String c1;
					while (!opStack.isEmpty()) {
						c1 = opStack.pop().toString();
						if (c1.charAt(0) != '#')
							postExp.add("" + c1);
					}
					i++;
					break;
				case ' ':
				case '\t':
					i++;
					break;
				default:
					if (Character.isDigit(ch) || ch == '.') {
						while (Character.isDigit(ch) || ch == '.') {
							numBuffer.append(ch);
							ch = exp.charAt(++i);
						}
						postExp.add(numBuffer.toString());
						numBuffer = new StringBuffer();
					} else {
						if (ch == 'Q')
							System.exit(0);
						throw new Exception("illegal operator");
					}
				}
			}
		} catch (RuntimeException e) {
			throw new Exception(e.getMessage());
		}
		return postExp;
	}
	// 定义优先级
	private int priority(char op) throws Exception {
		switch (op) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '(':
		case '#':
			return 0;
		}
		throw new Exception("Illegal operator");
	}
}

