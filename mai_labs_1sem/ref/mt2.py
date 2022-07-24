import ply.lex as lex
import ply.yacc as yacc
import re

tokens = [
	'VAR',
	'NUMBER',
	'PLUS',
	'MINUS',
	'MULTIPLY',
	'DIVIDE',
	'EQUALS'
]

t_VAR = r'[a-z]\w*'
t_NUMBER = r'\d+'
t_PLUS = r'\+'
t_MINUS = r'\-'
t_MULTIPLY = r'\*'
t_DIVIDE = r'\/'
t_EQUALS = r'\='

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

t_ignore  = ' \t'

def t_error(t):
    t.lexer.skip(1)

lexer = lex.lex()

precedence = (
	('left', 'PLUS','MINUS'),
	('left', 'MULTIPLY', 'DIVIDE')
)

def p_mt(p):
	'''
	mt : expression
	   | var_assign
	'''
	print(run(p[1]))

def p_expession(p):
	'''
	expression : expression MULTIPLY expression
	           | expression DIVIDE expression
	           | expression PLUS expression
	           | expression MINUS expression
	           | VAR PLUS expression
	           | expression PLUS VAR
	           | VAR PLUS VAR
	           | expression MINUS VAR
	           | VAR MINUS expression
	           | VAR MINUS VAR
	           | expression MULTIPLY VAR
	           | VAR MULTIPLY expression
	           | VAR MULTIPLY VAR
	           | expression DIVIDE VAR
	           | VAR DIVIDE expression
	           | VAR DIVIDE VAR
	
	'''
	p[0] = (p[2], p[1], p[3])

def p_expression_number(p):
	'''
	expression : NUMBER
	'''
	p[0] = p[1]
	
def p_var_assign(p):
	'''
	var_assign : VAR EQUALS expression
	'''
	p[0] = (p[2], p[1], p[3])

def p_error(p):
    print("Syntax error in input!")

parser = yacc.yacc()

mt_state = 0
var_memo = 0

def run(p):
	if type(p) == tuple:
		if p[0] == '+':
			return mt_plus(p[1], p[2])
		elif p[0] == '-':
			return mt_minus(p[1], p[2])
		elif p[0] == '*':
			return mt_multiply(p[1], p[2])
		elif p[0] == '/':
			return mt_divide(p[1], p[2])
		elif p[0] == '=':
			return mt_var_assign(p[1], p[2])	
	else:
		return p

def mt_plus(a, b):
	global mt_state
	global var_memo
	mt_code = ''
	if a.isdigit() and b.isdigit():
		mt_code += mt_read(a,b)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_left_shift_word(mt_state)
		mt_code += mt_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_insignificant_zeros(mt_state)
		mt_code += mt_inc_dec(mt_state)
		mt_code += mt_recovery(b)
		mt_code += mt_end(mt_state)
	else:
		if a.isdigit():
			mt_code += mt_read(a,b)
		elif b.isdigit():
			mt_code += mt_read(b,a)
		else:
			mt_code += mt_read(var_memo,a)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_var_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_inc_dec(mt_state)
		if a.isdigit():
			mt_code += mt_recovery(a)
		elif b.isdigit():
			mt_code += mt_recovery(b)
		else:
			mt_code += mt_recovery(var_memo)
		mt_code += mt_end(mt_state)
	mt_state = 0
	return mt_code

def mt_minus(a, b):
	global mt_state
	global var_memo
	if a.isdigit() and b.isdigit():
		mt_code = ''
		mt_code += mt_read(a,b)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_left_shift_word(mt_state)
		mt_code += mt_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_insignificant_zeros(mt_state)
		mt_code += mt_dec_dec(mt_state)
		mt_code += mt_recovery(b)
		mt_code += mt_end(mt_state)
	else:
		mt_code = ''
		if a.isdigit():
			mt_code += mt_read(a,b)
		elif b.isdigit():
			mt_code += mt_read(b,a)
		else:
			mt_code += mt_read(var_memo,a)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_var_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_dec_dec(mt_state)
		if a.isdigit():
			mt_code += mt_recovery(a)
		elif b.isdigit():
			mt_code += mt_recovery(b)
		else:
			mt_code += mt_recovery(var_memo)
		mt_code += mt_end(mt_state)
	mt_state = 0	
	return mt_code

def mt_multiply(a, b):
	global mt_state
	global var_memo
	if a.isdigit() and b.isdigit():
		mt_code = ''
		mt_code += mt_read(a, b)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_left_shift_word(mt_state)
		mt_code += mt_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_insignificant_zeros(mt_state)
		mt_code += mt_kardinal_cc(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_kardinal_multiply(mt_state)
		mt_code += mt_kardinal_recovery(mt_state)
		mt_code += mt_recovery(b)
		mt_code += mt_end(mt_state)
	else:
		mt_code = ''
		if a.isdigit():
			mt_code += mt_read(a,b)
		elif b.isdigit():
			mt_code += mt_read(b,a)
		else:
			mt_code += mt_read(var_memo,a)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_var_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_kardinal_cc(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_kardinal_multiply(mt_state)
		mt_code += mt_kardinal_recovery(mt_state)
		if a.isdigit():
			mt_code += mt_recovery(a)
		elif b.isdigit():
			mt_code += mt_recovery(b)
		else:
			mt_code += mt_recovery(var_memo)
		mt_code += mt_end(mt_state)
	mt_state = 0
	return mt_code

def mt_divide(a, b):
	global mt_state
	global var_memo
	if a.isdigit() and b.isdigit():
		mt_code = ''
		mt_code += mt_read(a, b)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_left_shift_word(mt_state)
		mt_code += mt_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_insignificant_zeros(mt_state)
		mt_code += mt_kardinal_cc(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_kardinal_divide(mt_state)
		mt_code += mt_recovery(b)
		mt_code += mt_end(mt_state)
	else:
		mt_code = ''
		if a.isdigit():
			mt_code += mt_read(a,b)
		elif b.isdigit():
			mt_code += mt_read(b,a)
		else:
			mt_code += mt_read(var_memo,a)
		mt_code += mt_left_lambda(mt_state)
		mt_code += mt_var_copy(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_kardinal_cc(mt_state)
		mt_code += mt_right_shift_word(mt_state)
		mt_code += mt_right_lambda(mt_state)
		mt_code += mt_kardinal_divide(mt_state)
		if a.isdigit():
			mt_code += mt_recovery(a)
		elif b.isdigit():
			mt_code += mt_recovery(b)
		else:
			mt_code += mt_recovery(var_memo)
		mt_code += mt_end(mt_state)
	mt_state = 0
	return mt_code

def mt_var_assign(a, b):
	global mt_state
	global var_memo
	mt_code = ''
	var_memo = b
	mt_code += mt_left_lambda(mt_state)
	mt_code += '%s,0,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	for i in range(len(b) - 1, -1, -1):
		mt_code += '%s, ,%s,%s\n' %(hex(mt_state)[2:] , b[i] , hex(mt_state + 1)[2:])
		mt_state += 1
		mt_code += '%s,%s,<,%s\n' %(hex	(mt_state)[2:] , b[i] , hex(mt_state)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,_,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_code += '%s,_,<,%s\n' %(hex(mt_state + 2)[2:], hex(mt_state + 3)[2:])
	mt_state += 3
	mt_code += '%s, ,%s,%s\n' %(hex(mt_state)[2:], a, hex(mt_state)[2:])
	mt_code += mt_right_var(mt_state)
	mt_code += '%s,_,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += mt_right_lambda(mt_state)
	mt_code += mt_right_shift_word(mt_state)
	mt_code += mt_right_lambda(mt_state)
	mt_code += mt_right_shift_word(mt_state)
	return mt_code

def mt_read(a, b):
	global mt_state
	mt_code = ''
	for i in range(len(a)):
		mt_code += '%s, ,%s,%s\n' %(hex(mt_state)[2:] , a[i] , hex(mt_state + 1)[2:])
		mt_state += 1
		mt_code += '%s,%s,>,%s\n' %(hex(mt_state)[2:] , a[i] , hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:] , hex(mt_state + 1)[2:])
	mt_state += 1
	for i in range(len(b)):
		mt_code += '%s, ,%s,%s\n' %(hex(mt_state)[2:] , b[i] , hex(mt_state + 1)[2:])
		mt_state += 1
		mt_code += '%s,%s,>,%s\n' %(hex(mt_state)[2:] , b[i] , hex(mt_state)[2:])
	return mt_code

def mt_recovery(b):
	global mt_state
	local_state = 1200
	mt_code = ''
	mt_code += ''.join('%s,9,=,%s\n' %(hex(mt_state)[2:] , hex(local_state)[2:]))
	for i in range(len(b)):
		mt_code += '%s,9,%s,%s\n' %(hex(local_state)[2:] , b[i] , hex(local_state + 1)[2:])
		local_state += 1
		if b[i] != '9':
			mt_code += '%s,%s,>,%s\n' %(hex(local_state)[2:] , b[i] , hex(local_state)[2:]) 
	mt_code += '%s, , ,%s\n' %(hex(local_state)[2:], hex(local_state + 1)[2:])
	mt_code += '%s,9,>,%s\n' %(hex(local_state)[2:], hex(local_state)[2:])
	local_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(local_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,9,>,%s\n' %(hex(local_state)[2:], hex(local_state)[2:])
	mt_state += 1
	mt_code += '%s,-,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += mt_right_shift_word(mt_state)
	return mt_code

def mt_copy(void):
	global mt_state
	local_state = 0
	mt_code = ''
	mt_code += mt_left_lambda(mt_state)
	mt_code += mt_left_shift_word(mt_state)
	mt_code += mt_right_lambda(mt_state)
	mt_code = mt_code + ''.join(['%s,%s, ,%s\n%s, ,>,%s\n' %(hex(mt_state)[2:] , hex(i - 1)[2:] , hex(10000 + i * 100)[2:] , hex(10000 + i * 100)[2:] , hex(10000 + i * 100 + 1)[2:]) for i in range(1, 11)])
	mt_code += local_copy(local_state)
	return mt_code

def mt_var_copy(void):
	global mt_state
	mt_code = ''
	mt_code += ''.join(['%s,%s, ,%s\n' %(hex(mt_state)[2:] , chr(i + 96) , hex(12000 + 100)[2:]) for i in range(1, 27)])
	mt_code += ''.join('%s, ,<,%s\n' %(hex(12000 + 100)[2:] , hex(12000 + 100 + 1)[2:]))
	local_state = 12100
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(local_state)[2:], hex(mt_state + 1)[2:])
	mt_code += mt_copy(mt_state)
	return mt_code

def mt_inc_dec(void):
	global mt_state
	local_state = 1100
	mt_code = ''
	mt_code += ''.join('%s, ,=,%s\n' %(hex(mt_state)[2:] , hex(local_state)[2:]))
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(i - 1)[2:], hex(local_state + 1)[2:]) for i in range(1,10)])
	mt_code += ''.join('%s,%s,%s,%s\n%s,%s,<,%s\n' %(hex(local_state)[2:], hex(0)[2:], hex(9)[2:], hex(local_state + 2)[2:], hex(local_state + 2)[2:], hex(9)[2:], hex(local_state)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)]) + ('%s, ,>,%s\n' %(hex(local_state)[2:] , hex(local_state + 2)[2:]))
	local_state += 2
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)]) + ('%s, ,<,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(i + 1)[2:], hex(local_state + 1)[2:]) for i in range(0,9)])
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state)[2:], hex(local_state + 4)[2:]))
	mt_code += ''.join('%s,9,0,%s\n' %(hex(local_state)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s,0,<,%s\n' %(hex(local_state + 2)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s, ,1,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 3)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,<,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(local_state)[2:]) for i in range(10)])
	mt_code += ''.join('%s, ,<,%s\n' %(hex(local_state)[2:], hex(local_state - 5)[2:]))
	local_state += 2
	mt_code += ''.join('%s,1, ,%s\n' %(hex(local_state)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state)[2:], hex(local_state + 1)[2:]))
	mt_code += ''.join('%s,0,1,%s\n' %(hex(local_state + 1)[2:], hex(local_state + 1)[2:]))
	mt_code += ''.join('%s,1,>,%s\n' %(hex(local_state + 1)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s,0,>,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s, , ,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 3)[2:]))
	mt_code += ''.join('%s, ,0,%s\n' %(hex(local_state + 3)[2:], hex(local_state - 2)[2:]))
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state - 7)[2:], hex(mt_state + 31)[2:]))
	mt_state += 31
	return mt_code

def mt_dec_dec(void):
	global mt_state
	local_state = 1100
	mt_code = ''
	mt_code += ''.join('%s, ,=,%s\n' %(hex(mt_state)[2:] , hex(local_state)[2:]))
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(i - 1)[2:], hex(local_state + 1)[2:]) for i in range(1,10)])
	mt_code += ''.join('%s,%s,%s,%s\n%s,%s,<,%s\n' %(hex(local_state)[2:], hex(0)[2:], hex(9)[2:], hex(local_state + 2)[2:], hex(local_state + 2)[2:], hex(9)[2:], hex(local_state)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)]) + ('%s, ,>,%s\n' %(hex(local_state)[2:] , hex(local_state + 2)[2:]))
	local_state += 2
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)])
	mt_code += ''.join('%s,-,>,%s\n' %(hex(local_state)[2:], hex(local_state + 13)[2:]))
	mt_code += ''.join('%s, ,<,%s\n' %(hex(local_state)[2:], hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(i - 1)[2:], hex(local_state + 1)[2:]) for i in range(1,10)])
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state)[2:], hex(local_state + 4)[2:]))
	mt_code += ''.join('%s,-,>,%s\n' %(hex(local_state)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s,0,9,%s\n' %(hex(local_state)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s,9,<,%s\n' %(hex(local_state + 2)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s, ,-,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 3)[2:]))
	local_state += 3
	mt_code += ''.join('%s,-, ,%s\n' %(hex(local_state)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state)[2:], hex(local_state + 1)[2:]))
	mt_code += ''.join('%s,9,-,%s\n' %(hex(local_state + 1)[2:], hex(local_state + 1)[2:]))
	mt_code += ''.join('%s,-,>,%s\n' %(hex(local_state + 1)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s,9, ,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 12)[2:]))
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state + 12)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s, ,<,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s,-,=,%s\n' %(hex(local_state + 2)[2:], hex(local_state + 3)[2:]))
	mt_code += ''.join('%s,-,>,%s\n' %(hex(local_state + 3)[2:], hex(local_state + 3)[2:]))
	mt_code += ''.join('%s, ,1,%s\n' %(hex(local_state + 3)[2:], hex(local_state + 4)[2:]))
	mt_code += ''.join('%s,9,1,%s\n' %(hex(local_state + 3)[2:], hex(local_state + 4)[2:]))
	local_state -= 2
	mt_code += ''.join(['%s,%s,<,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)])
	mt_code += ''.join('%s,-,<,%s\n' %(hex(local_state)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s, ,<,%s\n' %(hex(local_state)[2:], hex(local_state - 5)[2:]))
	local_state += 6
	mt_code += ''.join(['%s,%s,<,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)])
	mt_code += ''.join('%s,-,<,%s\n' %(hex(local_state)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s, ,<,%s\n' %(hex(local_state)[2:], hex(local_state - 11)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(i + 1)[2:], hex(local_state + 1)[2:]) for i in range(0,9)])
	mt_code += ''.join('%s,9,0,%s\n' %(hex(local_state)[2:], hex(local_state + 2)[2:]))
	mt_code += ''.join('%s,0,<,%s\n' %(hex(local_state + 2)[2:], hex(local_state)[2:]))
	mt_code += ''.join('%s,-,>,%s\n' %(hex(local_state)[2:], hex(local_state + 6)[2:]))
	mt_code += ''.join('%s,0,1,%s\n' %(hex(local_state + 6)[2:], hex(local_state + 6)[2:]))
	mt_code += ''.join('%s,1,>,%s\n' %(hex(local_state + 6)[2:], hex(local_state + 3)[2:]))
	mt_code += ''.join('%s,0,>,%s\n' %(hex(local_state + 3)[2:], hex(local_state + 3)[2:]))
	mt_code += ''.join('%s, ,0,%s\n' %(hex(local_state + 3)[2:], hex(local_state - 7)[2:]))
	local_state += 1
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(local_state)[2:], hex(i + 1)[2:], hex(local_state - 2)[2:]) for i in range(0,9)])
	local_state += 3
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(local_state)[2:], hex(i)[2:], hex(local_state)[2:]) for i in range(10)])
	mt_code += ''.join('%s, ,<,%s\n' %(hex(local_state)[2:], hex(local_state - 4)[2:]))
	mt_code += ''.join('%s, ,>,%s\n' %(hex(local_state - 16)[2:], hex(mt_state + 31)[2:]))
	mt_state += 31
	return mt_code
	
def local_copy(local_state):
	mt_code = ''
	local_state = 10101
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,0,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,0,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,0,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10201
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,1,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,1,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,1,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10301
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,2,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,2,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,2,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10401
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,3,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,3,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,3,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10501
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,4,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,4,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,4,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10601
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,5,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,5,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,5,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10701
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,6,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,6,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,6,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))

	local_state = 10801
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,7,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,7,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,7,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 10901
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,8,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,8,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,8,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	
	local_state = 11001
	
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += local_right_lambda(local_state)
	local_state += 1
	mt_code += local_right_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,9,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += local_left_lambda(local_state)
	local_state += 1
	mt_code += local_left_shift_word(local_state)
	local_state += 1
	mt_code += ''.join('%s, ,9,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	local_state += 1
	mt_code += ''.join('%s,9,>,%s\n' %(hex(local_state)[2:] , hex(mt_state)[2:]))
	return mt_code
	
def mt_insignificant_zeros(void):
	global mt_state
	mt_code = ''
	mt_code += mt_left_shift_word(mt_state)
	mt_code += mt_right_lambda(mt_state)
	mt_code += ''.join('%s,0, ,%s\n' %(hex(mt_state)[2:] , hex(mt_state + 1)[2:]))
	mt_state += 1
	mt_code += mt_right_lambda(mt_state)
	local_state = mt_state
	mt_code += ''.join(['%s,%s, ,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state + i)[2:]) for i in range(1,11)])
	mt_code += ''.join(['%s, ,<,%s\n' %(hex(local_state + i)[2:] , hex(local_state + i + 10)[2:]) for i in range(1,11)])
	mt_code += ''.join(['%s, ,%s,%s\n' %(hex(local_state + i + 10)[2:] , hex(i - 1)[2:] , hex(local_state + i + 20)[2:]) for i in range(1,11)])
	mt_code += ''.join(['%s,%s,>,%s\n%s, ,>,%s\n' %(hex(local_state + i + 20)[2:] , hex(i - 1)[2:] , hex(local_state + i + 20)[2:] , hex(local_state + i + 20)[2:] , hex(mt_state)[2:]) for i in range(1,11)])
	return mt_code

def mt_kardinal_cc(void):
	global mt_state
	mt_code = ''
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 31)[2:])
	mt_state += 31
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += local_left_shift_word(mt_state)
	mt_state += 1
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(i - 1)[2:], hex(mt_state + 1)[2:]) for i in range(1,10)])
	mt_code += ''.join('%s,%s,%s,%s\n%s,%s,<,%s\n' %(hex(mt_state)[2:], hex(0)[2:], hex(9)[2:], hex(mt_state + 2)[2:], hex(mt_state + 2)[2:], hex(9)[2:], hex(mt_state)[2:])) 
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,=,%s\n' %(hex(mt_state)[2:], hex(mt_state - 9)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state - 7)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(i - 1)[2:], hex(mt_state + 1)[2:]) for i in range(1,10)])
	mt_code += ''.join('%s,%s,%s,%s\n%s,%s,<,%s\n' %(hex(mt_state)[2:], hex(0)[2:], hex(9)[2:], hex(mt_state + 2)[2:], hex(mt_state + 2)[2:], hex(9)[2:], hex(mt_state)[2:])) 
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state - 6)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state - 7)[2:], hex(mt_state)[2:])
	return mt_code

def mt_kardinal_multiply(void):
	global mt_state
	mt_code = ''
	mt_code += '%s,|,q,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,q,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,w,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,w,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,w,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_state += 1
	mt_code += '%s,|,w,%s\n' %(hex(mt_state)[2:], hex(mt_state - 5)[2:])
	mt_state += 1
	mt_code += '%s,w,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,|,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_state += 2
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,q,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,|,>,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_code += '%s,|,q,%s\n' %(hex(mt_state + 2)[2:], hex(mt_state - 11)[2:])
	mt_state += 2
	return mt_code
	
def mt_kardinal_divide(void):
	global mt_state
	mt_code = ''
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state - 8)[2:])
	mt_code += '%s, ,e,%s\n' %(hex(mt_state - 8)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,e,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,w,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,w,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,q,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,q,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,q,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state - 6)[2:])
	mt_code += '%s,q,|,%s\n' %(hex(mt_state - 2)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,w,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,|,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,w,=,%s\n' %(hex(mt_state)[2:], hex(mt_state - 10)[2:])
	mt_code += '%s,e, ,%s\n' %(hex(mt_state - 6)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,q, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,w, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state)[2:])
	mt_code += '%s,9,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_state += 2
	
	mt_code += '%s,9, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state - 1)[2:])
	mt_state += 1
	mt_code += '%s, ,0,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,q,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,q,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,|,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state + 1)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(i + 1)[2:], hex(mt_state + 6)[2:]) for i in range(9)])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 3)[2:])
	mt_code += '%s,9,0,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,0,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,1,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_state += 2
	mt_code += '%s,1, ,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,0,1,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,1,>,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_code += '%s,0,>,%s\n' %(hex(mt_state + 2)[2:], hex(mt_state + 2)[2:])
	mt_code += '%s, , ,%s\n' %(hex(mt_state + 2)[2:], hex(mt_state + 3)[2:])
	mt_code += '%s, ,0,%s\n' %(hex(mt_state + 3)[2:], hex(mt_state + 4)[2:])
	mt_state += 4
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state)[2:]) for i in range(10)])
	mt_code += ''.join('%s, ,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:]))
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,q, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state - 7)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state - 8)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state + 1)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += local_left_shift_word(mt_state)
	mt_state += 1
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += local_left_shift_word(mt_state)
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	return mt_code

def mt_kardinal_recovery(void):
	global mt_state
	mt_code = ''
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,q,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,q,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,|,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,|,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += '%s,9, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state - 1)[2:])
	mt_state += 1
	mt_code += '%s, ,0,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += local_right_shift_word(mt_state)
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_state += 2
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_state += 2
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state + 1)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += ''.join(['%s,%s,%s,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(i + 1)[2:], hex(mt_state + 6)[2:]) for i in range(9)])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 3)[2:])
	mt_code += '%s,9,0,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,0,<,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,1,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_state += 2
	mt_code += '%s,1, ,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,0,1,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,1,>,%s\n' %(hex(mt_state + 1)[2:], hex(mt_state + 2)[2:])
	mt_code += '%s,0,>,%s\n' %(hex(mt_state + 2)[2:], hex(mt_state + 2)[2:])
	mt_code += '%s, , ,%s\n' %(hex(mt_state + 2)[2:], hex(mt_state + 3)[2:])
	mt_code += '%s, ,0,%s\n' %(hex(mt_state + 3)[2:], hex(mt_state + 4)[2:])
	mt_state += 4
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state)[2:]) for i in range(10)])
	mt_code += ''.join('%s, ,=,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:]))
	mt_state += 1
	mt_code += '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += '%s,|, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_code += '%s,q, ,%s\n' %(hex(mt_state)[2:], hex(mt_state + 2)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state - 7)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state - 8)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state)[2:])
	mt_code += ''.join(['%s,%s,=,%s\n' %(hex(mt_state)[2:], hex(i)[2:], hex(mt_state + 1)[2:]) for i in range(10)])
	mt_state += 1
	mt_code += local_left_shift_word(mt_state)
	mt_state += 1
	mt_code += local_left_lambda(mt_state)
	mt_state += 1
	mt_code += local_left_shift_word(mt_state)
	mt_state += 1
	mt_code += local_right_lambda(mt_state)
	mt_state += 1
	return mt_code

def mt_left_lambda(void):
	global mt_state
	mt_code = '%s, ,<,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	return mt_code

def mt_left_shift_word(void):
	global mt_state
	mt_code = ''.join(['%s,%s,<,%s\n' %(hex(mt_state)[2:] , hex(i - 1)[2:] , hex(mt_state)[2:]) for i in range(1, 11)]) + ('%s, ,=,%s\n' %(hex(mt_state)[2:] , hex(mt_state + 1)[2:]))
	mt_state += 1
	return mt_code 

def mt_right_lambda(void):
	global mt_state
	mt_code = '%s, ,>,%s\n' %(hex(mt_state)[2:], hex(mt_state + 1)[2:])
	mt_state += 1
	return mt_code
	
def mt_right_shift_word(void):
	global mt_state
	mt_code = ''.join(['%s,%s,>,%s\n' %(hex(mt_state)[2:] , hex(i - 1)[2:] , hex(mt_state)[2:]) for i in range(1, 11)]) + ('%s, ,=,%s\n' %(hex(mt_state)[2:] , hex(mt_state + 1)[2:]))
	mt_state += 1
	return mt_code 

def local_left_shift_word(local_state):
	mt_code = ''.join(['%s,%s,<,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)]) + ('%s, ,=,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	return mt_code

def local_left_lambda(local_state):
	mt_code = '%s, ,<,%s\n' %(hex(local_state)[2:], hex(local_state + 1)[2:])
	return mt_code
	
def local_right_shift_word(local_state):
	mt_code = ''.join(['%s,%s,>,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state)[2:]) for i in range(1, 11)]) + ('%s, ,=,%s\n' %(hex(local_state)[2:] , hex(local_state + 1)[2:]))
	return mt_code

def local_right_lambda(local_state):
	mt_code = '%s, ,>,%s\n' %(hex(local_state)[2:], hex(local_state + 1)[2:])
	return mt_code

def local_right_shift(local_state):
	mt_code = ''.join(['%s,%s,<,%s\n' %(hex(local_state)[2:] , hex(i - 1)[2:] , hex(local_state + 1)[2:]) for i in range(1, 11)])
	return mt_code

def mt_right_var(mt_state):
	mt_code = ''
	mt_code += ''.join(['%s,%s,>,%s\n' %(hex(mt_state)[2:], chr(i + 97), hex(mt_state)[2:]) for i in range(26)])
	return mt_code
	
def mt_left_var(mt_state):
	mt_code = ''
	mt_code += ''.join(['%s,%s,<,%s\n' %(hex(mt_state)[2:], chr(i + 97), hex(mt_state)[2:]) for i in range(26)])
	return mt_code

def mt_end(void):
	global mt_state
	mt_code = ''
	mt_code += ''.join('%s, ,#,0\n' %(hex(mt_state)[2:]))
	return mt_code

while True:
   try:
       s = input('')
   except EOFError:
       break
   if not s: continue
   result = parser.parse(s)
