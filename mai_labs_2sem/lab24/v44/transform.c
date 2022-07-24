#include "tree.h"
#include "transform.h"
#include <math.h>
#include "vector.h"

int check_reverse(Tree t)
{
	int cmp = 0;
	if (t == NULL)
		return -1;
	if ((t->left == NULL || t->right == NULL) && (t->node.type != INTEGER) && (t->node.type != VARIABLE)) {
		return -1;
	} else if ((t->left == NULL || t->right == NULL) && ((t->node.type == INTEGER) || (t->node.type == VARIABLE))) {
		return 1;
	}

	if ((t->node.type == OPERATOR) && ((t->node.data.operator_name == '+') || (t->node.data.operator_name == '-'))) {
		if ((t->right->node.type == INTEGER)) {
			cmp = 0;
		} else if (t->right->node.type == VARIABLE) {
			cmp = 1;
		} else if ((t->right->node.type == OPERATOR) && (t->right->node.data.operator_name == '^')) {
			if (t->right->right->node.type == INTEGER) {
				cmp = t->right->right->node.data.value_int;
			}
		} else if ((t->right->node.type == OPERATOR) && (t->right->node.data.operator_name == '*')) {
			if (t->right->right != NULL) {
				if ((t->right->right->node.type == OPERATOR) && (t->right->right->node.data.operator_name == '^')){
					if ((t->right->right->left != NULL) && (t->right->right->right != NULL)) {
						if ((t->right->right->left->node.type == VARIABLE) && (t->right->right->right->node.type == INTEGER)) {
						cmp = t->right->right->right->node.data.value_int;
						} else {
							return -1;
						}
					} else {
						return -1;
					}       
				} else if ((t->right->left->node.type == OPERATOR) && (t->right->left->node.data.operator_name == '^')) {
					if ((t->right->left->left != NULL) && (t->right->left->right != NULL)) {
						if ((t->right->left->left->node.type == VARIABLE) && (t->right->left->right->node.type == INTEGER)) {
							cmp = t->right->left->right->node.data.value_int;
						} else {
							return -1;
						}
					} else {
						return -1;
					}
				}
			} else {
				return -1;
			}
		} else {
			return -1;
		}
		Tree tmp = t;
		while ((tmp->node.type == OPERATOR) && ((tmp->node.data.operator_name == '+') || (tmp->node.data.operator_name == '-'))) {
			if ((tmp->left->node.type == OPERATOR) && ((tmp->left->node.data.operator_name == '+') || (tmp->left->node.data.operator_name == '-'))) {
				tmp = tmp->left;
			} else if ((tmp->left->node.type == INTEGER)) {
				if (cmp > 0) {
					return 0;
				} else {
					break;
				}
			} else if (tmp->left->node.type == VARIABLE) {
				if (cmp > 1) {
					return 0;
				} else {
					break;
				}
			} else if ((tmp->left->node.type == OPERATOR) && (tmp->left->node.data.operator_name == '^')) {
				if (tmp->left->right->node.data.value_int > cmp) {
					break;
				} else {
					return 0;
				}
			} else if ((tmp->left->node.type == OPERATOR) && (tmp->left->node.data.operator_name == '*')) {
				if ((tmp->left->left != NULL) && (tmp->left->right != NULL)) {
					if ((tmp->left->right->node.type == OPERATOR) && (tmp->left->right->node.data.operator_name == '^')) {
						if ((tmp->left->right->right->node.data.value_int > cmp)) {
							break;
						} else {
							return 0;
						}
					} else if ((tmp->left->left->node.type == OPERATOR) && (tmp->left->left->node.data.operator_name == '^')) {
						if ((tmp->left->left->right->node.data.value_int > cmp)) {
							break;
						} else {
							return 0;
						}
					} else if (((tmp->left->left->node.type == INTEGER) && (tmp->left->right->node.type == VARIABLE)) || 
					((tmp->left->left->node.type == VARIABLE) && (tmp->left->right->node.type == INTEGER))) {
						if (cmp > 1) {
							return 0;
						} else {
							break;
						}
					} else {
						return -1;
					}
				} else {
					return -1;
				}
			} else {
				break;
			}

			if (tmp->right->node.type == INTEGER) {
				if (cmp > 0) {
					return 0;
				} else {
					continue;
				}
			} else if (tmp->right->node.type == VARIABLE) {
				if (cmp > 1) {
					return 0;
				} else {
					continue;
				}
			} else if ((tmp->right->node.type == OPERATOR) && (tmp->right->node.data.operator_name == '^')) {
				if (tmp->right->right->node.type == INTEGER) {
					if (tmp->right->right->node.data.value_int > cmp) {
						cmp = tmp->right->right->node.data.value_int;
					} else {
						return 0;
					}
				} else {
					return -1;
				}
			} else if ((tmp->right->node.type == OPERATOR) && (tmp->right->node.data.operator_name == '*')) {
				if ((tmp->right->left != NULL) && (tmp->right->right != NULL)) {
					if ((tmp->right->right->node.type == OPERATOR) && (tmp->right->right->node.data.operator_name == '^')) {
						if ((tmp->right->right->right->node.data.value_int > cmp)) {
							cmp = tmp->right->right->right->node.data.value_int;
						} else {
							return 0;
						}
					} else if ((tmp->right->left->node.type == OPERATOR) && (tmp->right->left->node.data.operator_name == '^')) {
						if ((tmp->right->left->right->node.data.value_int > cmp)) {
							cmp = tmp->right->left->right->node.data.value_int;
						} else {
							return 0;
						}
					} else if (((tmp->right->left->node.type == INTEGER) && (tmp->right->right->node.type == VARIABLE)) || 
					((tmp->right->left->node.type == VARIABLE) && (tmp->right->right->node.type == INTEGER))) {
						if (cmp > 1) {
							return 0;
						} else {
							cmp = 1;
						}
					} else {
						return -1;
					}
				} else {
					return -1;
				}
			}
		}
        
	} else if ((t->node.type == OPERATOR) && (t->node.data.operator_name == '*')) {
		if ((t->right->node.type == VARIABLE) || (t->left->node.type == VARIABLE) || (t->right->node.type == INTEGER) || (t->left->node.type == INTEGER)) {
			return 1;
		}
		} else if ((t->node.type == OPERATOR) && (t->node.data.operator_name == '^')) {
			if ((t->right->node.type == INTEGER) && (t->left->node.type == VARIABLE)) {
				return 1;
			}
		} else {
			return -1;
		}
	return 1;
}


int check_right(Tree t)
{
	int cmp = 0;
	if (t == NULL)
		return -1;
	if ((t->left == NULL || t->right == NULL) && (t->node.type != INTEGER) && (t->node.type != VARIABLE)) {
		return -1;
	} else if ((t->left == NULL || t->right == NULL) && ((t->node.type == INTEGER) || (t->node.type == VARIABLE))) {
		return 1;
	}

	if ((t->node.type == OPERATOR) && ((t->node.data.operator_name == '+') || (t->node.data.operator_name == '-'))) {
		if ((t->right->node.type == INTEGER)) {
			cmp = 0;
		} else if (t->right->node.type == VARIABLE) {
			cmp = 1;
		} else if ((t->right->node.type == OPERATOR) && (t->right->node.data.operator_name == '^')) {
			if (t->right->right->node.type == INTEGER) {
				cmp = t->right->right->node.data.value_int;
			}
		} else if ((t->right->node.type == OPERATOR) && (t->right->node.data.operator_name == '*')) {
			if (t->right->right != NULL) {
				if ((t->right->right->node.type == OPERATOR) && (t->right->right->node.data.operator_name == '^')){
					if ((t->right->right->left != NULL) && (t->right->right->right != NULL)) {
						if ((t->right->right->left->node.type == VARIABLE) && (t->right->right->right->node.type == INTEGER)) {
						cmp = t->right->right->right->node.data.value_int;
						} else {
							return -1;
						}
					} else {
						return -1;
					}       
				} else if ((t->right->left->node.type == OPERATOR) && (t->right->left->node.data.operator_name == '^')) {
					if ((t->right->left->left != NULL) && (t->right->left->right != NULL)) {
						if ((t->right->left->left->node.type == VARIABLE) && (t->right->left->right->node.type == INTEGER)) {
							cmp = t->right->left->right->node.data.value_int;
						} else {
							return -1;
						}
					} else {
						return -1;
					}
				}
			} else {
				return -1;
			}
		} else {
			return -1;
		}
		Tree tmp = t;
		while ((tmp->node.type == OPERATOR) && ((tmp->node.data.operator_name == '+') || (tmp->node.data.operator_name == '-'))) {
			if ((tmp->left->node.type == OPERATOR) && ((tmp->left->node.data.operator_name == '+') || (tmp->left->node.data.operator_name == '-'))) {
				tmp = tmp->left;
			} else if ((tmp->left->node.type == INTEGER)) {
				if (cmp < 0) {
					return 0;
				} else {
					break;
				}
			} else if (tmp->left->node.type == VARIABLE) {
				if (cmp < 1) {
					return 0;
				} else {
					break;
				}
			} else if ((tmp->left->node.type == OPERATOR) && (tmp->left->node.data.operator_name == '^')) {
				if (tmp->left->right->node.data.value_int < cmp) {
					break;
				} else {
					return 0;
				}
			} else if ((tmp->left->node.type == OPERATOR) && (tmp->left->node.data.operator_name == '*')) {
				if ((tmp->left->left != NULL) && (tmp->left->right != NULL)) {
					if ((tmp->left->right->node.type == OPERATOR) && (tmp->left->right->node.data.operator_name == '^')) {
						if ((tmp->left->right->right->node.data.value_int < cmp)) {
							break;
						} else {
							return 0;
						}
					} else if ((tmp->left->left->node.type == OPERATOR) && (tmp->left->left->node.data.operator_name == '^')) {
						if ((tmp->left->left->right->node.data.value_int < cmp)) {
							break;
						} else {
							return 0;
						}
					} else if (((tmp->left->left->node.type == INTEGER) && (tmp->left->right->node.type == VARIABLE)) || 
					((tmp->left->left->node.type == VARIABLE) && (tmp->left->right->node.type == INTEGER))) {
						if (cmp < 1) {
							return 0;
						} else {
							break;
						}
					} else {
						return -1;
					}
				} else {
					return -1;
				}
			} else {
				break;
			}

			if (tmp->right->node.type == INTEGER) {
				if (cmp < 0) {
					return 0;
				} else {
					continue;
				}
			} else if (tmp->right->node.type == VARIABLE) {
				if (cmp < 1) {
					return 0;
				} else {
					continue;
				}
			} else if ((tmp->right->node.type == OPERATOR) && (tmp->right->node.data.operator_name == '^')) {
				if (tmp->right->right->node.type == INTEGER) {
					if (tmp->right->right->node.data.value_int < cmp) {
						cmp = tmp->right->right->node.data.value_int;
					} else {
						return 0;
					}
				} else {
					return -1;
				}
			} else if ((tmp->right->node.type == OPERATOR) && (tmp->right->node.data.operator_name == '*')) {
				if ((tmp->right->left != NULL) && (tmp->right->right != NULL)) {
					if ((tmp->right->right->node.type == OPERATOR) && (tmp->right->right->node.data.operator_name == '^')) {
						if ((tmp->right->right->right->node.data.value_int < cmp)) {
							cmp = tmp->right->right->right->node.data.value_int;
						} else {
							return 0;
						}
					} else if ((tmp->right->left->node.type == OPERATOR) && (tmp->right->left->node.data.operator_name == '^')) {
						if ((tmp->right->left->right->node.data.value_int < cmp)) {
							cmp = tmp->right->left->right->node.data.value_int;
						} else {
							return 0;
						}
					} else if (((tmp->right->left->node.type == INTEGER) && (tmp->right->right->node.type == VARIABLE)) || 
					((tmp->right->left->node.type == VARIABLE) && (tmp->right->right->node.type == INTEGER))) {
						if (cmp < 1) {
							return 0;
						} else {
							cmp = 1;
						}
					} else {
						return -1;
					}
				} else {
					return -1;
				}
			}
		}
        
	} else if ((t->node.type == OPERATOR) && (t->node.data.operator_name == '*')) {
		if ((t->right->node.type == VARIABLE) || (t->left->node.type == VARIABLE) || (t->right->node.type == INTEGER) || (t->left->node.type == INTEGER)) {
			return 1;
		}
		} else if ((t->node.type == OPERATOR) && (t->node.data.operator_name == '^')) {
			if ((t->right->node.type == INTEGER) && (t->left->node.type == VARIABLE)) {
				return 1;
			}
		} else {
			return -1;
		}
	return 1;
}