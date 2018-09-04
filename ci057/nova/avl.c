avl_pp generate_avl(int *arr, int len)
{
	int i = 0;
	avl_pp head = NULL;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	head = init_avl();

	for (; i < len; i++) {
		if (insert_avl_node(head, arr[i]) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head);
			return NULL;
		}
	}

	return head;
}

/*
 * Initialize an AVL tree with empty root node
 */
avl_pp init_avl(void)
{
	avl_pp head = calloc(1, sizeof(avl_p));
	*head = NULL;

	return head;
}

/*
 * Insert a new node into AVL tree
 */
bool insert_avl_node(avl_pp head, int val)
{
	avl_p root = NULL;
	nodedata_p p = NULL;
	nodedata_p n = NULL;
	bool modified;
	/* Stack to rebalance each subtree bottom-up after insertion */
	stack_p stack = get_stack();

	if (!head) {
		log(ERROR, "Initialize AVL tree first\n");
		return FALSE;
	}

	root = *head;

	if (!root) {
		root = (avl_p) calloc(1, sizeof(avl_t));
		root->data = val;
		*head = root;

		return TRUE;
	}

	while (root) {
		if (val < root->data) {
			if (!root->left) {
				/* Create an AVL node for new value */
				root->left = calloc(1, sizeof(avl_t));
				root->left->data = val;
				root->height = height(root);

				modified = FALSE;

				/* Unwind stack & rebalance nodes (only once) */
				while ((p = pop(stack)) != NULL) {
					/* One rebalance for one insertion */
					if (!modified) {
						modified = rebalance(stack,
								head, p->node, val);
					}

					free(p);
				}

				break;
			}

			/* Push the parent node and traversal
			   direction in stack as we traverse down */
			n = malloc(sizeof(nodedata));
			n->node = root;
			n->direction = LEFT;
			push(stack, n);

			/* Traverse further left */
			root = root->left;
		} else {
			if (!root->right) {
				root->right = calloc(1, sizeof(avl_t));
				root->right->data = val;
				root->height = height(root);

				modified = FALSE;

				while ((p = pop(stack)) != NULL) {
					if (!modified) {
						modified = rebalance(stack,
								head, p->node, val);
					}

					free(p);
				}

				break;
			}

			n = malloc(sizeof(nodedata));
			n->node = root;
			n->direction = RIGHT;
			push(stack, n);

			root = root->right;
		}
	}

	destroy_stack(stack);

	return TRUE;
}

/*
 * Delete a node from AVL tree
 * Recursive method
 */
bool delete_avl_node(avl_pp head, int val)
{
	avl_p node;
	avl_p tmp;

	if (!head) {
		log(ERROR, "Initialize AVL tree first\n");
		return FALSE;
	}

	node = *head;
	if (!node) {
		log(ERROR, "No nodes to delete\n");
		return FALSE;
	}

	if (val > node->data) {
		if (!node->right)
			return FALSE;

		if (delete_avl_node(&(node->right), val) == FALSE)
			return FALSE;

		if (BalanceFactor(node) == 2) {
			if (BalanceFactor(node->left) >= 0)
				node = LeftLeft(node);
			else
				node = LeftRight(node);
		}
	} else if (val < node->data) {
		if (!node->left)
			return FALSE;

		if (delete_avl_node(&(node->left), val) == FALSE)
			return FALSE;

		if (BalanceFactor(node) == -2) {
			if (BalanceFactor(node->right) <= 0)
				node = RightRight(node);
			else
				node = RightLeft(node);
		}
	} else { /* Match found */
		if (node->right) {  /* Delete the inorder successor */
			tmp = node->right;
			while (tmp->left)
				tmp = tmp->left;

			node->data = tmp->data;
			if (delete_avl_node(&(node->right), tmp->data) == FALSE)
				return FALSE;

			if (BalanceFactor(node) == 2) {
				if (BalanceFactor(node->left) >= 0)
					node = LeftLeft(node);
				else
					node = LeftRight(node);
			}
		} else {
			*head = node->left;
			return TRUE;
		}
	}

	node->height = height(node);
	*head = node;
	return TRUE;
}

/*
 * Destroy an AVL tree
 */
int destroy_avl(avl_pp head)
{
	int count = 0;

	if (!head) {
		log(ERROR, "head invalid.\n");
		return -1;
	}

	count = delete_avl_nodes(*head);

	free(head);
	head = NULL;

	return count;
}

/*
 * Print the values in an AVL tree in preorder
 */
int print_avl(avl_p root, avl_p parent)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	++count;

	/* Print data value in the node */
	log(INFO, "data: %6d,  parent: %6d\n", root->data, parent->data);

	if (root->left) {
		log(INFO, "LEFT.\n");
		count += print_avl(root->left, root);
	}

	if (root->right) {
		log(INFO, "RIGHT.\n");
		count += print_avl(root->right, root);
	}

	return count;
}avl_pp generate_avl(int *arr, int len)
{
	int i = 0;
	avl_pp head = NULL;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	head = init_avl();

	for (; i < len; i++) {
		if (insert_avl_node(head, arr[i]) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head);
			return NULL;
		}
	}

	return head;
}

/*
 * Initialize an AVL tree with empty root node
 */
avl_pp init_avl(void)
{
	avl_pp head = calloc(1, sizeof(avl_p));
	*head = NULL;

	return head;
}

/*
 * Insert a new node into AVL tree
 */
bool insert_avl_node(avl_pp head, int val)
{
	avl_p root = NULL;
	nodedata_p p = NULL;
	nodedata_p n = NULL;
	bool modified;
	/* Stack to rebalance each subtree bottom-up after insertion */
	stack_p stack = get_stack();

	if (!head) {
		log(ERROR, "Initialize AVL tree first\n");
		return FALSE;
	}

	root = *head;

	if (!root) {
		root = (avl_p) calloc(1, sizeof(avl_t));
		root->data = val;
		*head = root;

		return TRUE;
	}

	while (root) {
		if (val < root->data) {
			if (!root->left) {
				/* Create an AVL node for new value */
				root->left = calloc(1, sizeof(avl_t));
				root->left->data = val;
				root->height = height(root);

				modified = FALSE;

				/* Unwind stack & rebalance nodes (only once) */
				while ((p = pop(stack)) != NULL) {
					/* One rebalance for one insertion */
					if (!modified) {
						modified = rebalance(stack,
								head, p->node, val);
					}

					free(p);
				}

				break;
			}

			/* Push the parent node and traversal
			   direction in stack as we traverse down */
			n = malloc(sizeof(nodedata));
			n->node = root;
			n->direction = LEFT;
			push(stack, n);

			/* Traverse further left */
			root = root->left;
		} else {
			if (!root->right) {
				root->right = calloc(1, sizeof(avl_t));
				root->right->data = val;
				root->height = height(root);

				modified = FALSE;

				while ((p = pop(stack)) != NULL) {
					if (!modified) {
						modified = rebalance(stack,
								head, p->node, val);
					}

					free(p);
				}

				break;
			}

			n = malloc(sizeof(nodedata));
			n->node = root;
			n->direction = RIGHT;
			push(stack, n);

			root = root->right;
		}
	}

	destroy_stack(stack);

	return TRUE;
}

/*
 * Delete a node from AVL tree
 * Recursive method
 */
bool delete_avl_node(avl_pp head, int val)
{
	avl_p node;
	avl_p tmp;

	if (!head) {
		log(ERROR, "Initialize AVL tree first\n");
		return FALSE;
	}

	node = *head;
	if (!node) {
		log(ERROR, "No nodes to delete\n");
		return FALSE;
	}

	if (val > node->data) {
		if (!node->right)
			return FALSE;

		if (delete_avl_node(&(node->right), val) == FALSE)
			return FALSE;

		if (BalanceFactor(node) == 2) {
			if (BalanceFactor(node->left) >= 0)
				node = LeftLeft(node);
			else
				node = LeftRight(node);
		}
	} else if (val < node->data) {
		if (!node->left)
			return FALSE;

		if (delete_avl_node(&(node->left), val) == FALSE)
			return FALSE;

		if (BalanceFactor(node) == -2) {
			if (BalanceFactor(node->right) <= 0)
				node = RightRight(node);
			else
				node = RightLeft(node);
		}
	} else { /* Match found */
		if (node->right) {  /* Delete the inorder successor */
			tmp = node->right;
			while (tmp->left)
				tmp = tmp->left;

			node->data = tmp->data;
			if (delete_avl_node(&(node->right), tmp->data) == FALSE)
				return FALSE;

			if (BalanceFactor(node) == 2) {
				if (BalanceFactor(node->left) >= 0)
					node = LeftLeft(node);
				else
					node = LeftRight(node);
			}
		} else {
			*head = node->left;
			return TRUE;
		}
	}

	node->height = height(node);
	*head = node;
	return TRUE;
}

/*
 * Destroy an AVL tree
 */
int destroy_avl(avl_pp head)
{
	int count = 0;

	if (!head) {
		log(ERROR, "head invalid.\n");
		return -1;
	}

	count = delete_avl_nodes(*head);

	free(head);
	head = NULL;

	return count;
}

/*
 * Print the values in an AVL tree in preorder
 */
int print_avl(avl_p root, avl_p parent)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	++count;

	/* Print data value in the node */
	log(INFO, "data: %6d,  parent: %6d\n", root->data, parent->data);

	if (root->left) {
		log(INFO, "LEFT.\n");
		count += print_avl(root->left, root);
	}

	if (root->right) {
		log(INFO, "RIGHT.\n");
		count += print_avl(root->right, root);
	}

	return count;
}
