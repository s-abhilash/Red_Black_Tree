#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEFT 0
#define RIGHT 1

#define FOUND 1
#define NOT_FOUND 0

#define SWAP_COLOR 1
#define DO_NOT_SWAP_COLOR 0

typedef enum 
{
    black,
    red,
    double_black
} color_t; 

/* Typedef of binary tree */
typedef struct bst
{
    int data;
    struct bst *left;
    struct bst *right;
    color_t color;
} bst_t;
 
/* Function prototypes */
bst_t *create_node(int data, color_t color);
bst_t *insert_node(bst_t *root, int data, color_t color);
int find_min(bst_t *root);
int find_max(bst_t *root);
void print_in_order(bst_t *root);
void print_pre_order(bst_t *root);
void print_post_order(bst_t *root);
bst_t *find_element(bst_t *root, int element);
bst_t *delete_node(bst_t **tree_root, bst_t *root, bst_t *parent, int element);
int delete_node1(bst_t **tree_root, bst_t *root, bst_t *parent, int element);
int height_of_tree(bst_t *node);
int count_node(bst_t *n);
bst_t *rotate_right(bst_t **tree_root, bst_t *root, bst_t *parent, int data, int swap_color);
bst_t *rotate_left(bst_t **tree_root, bst_t *root, bst_t *parent, int data, int swap_color);
int find_double_red(bst_t *root, bst_t *parent, bst_t **dred_root, bst_t **dred_parent, int double_red);
int resolve_doublered(bst_t **tree_root, bst_t *root, bst_t *parent);
int get_rotation_type(bst_t *root, bst_t *parent);
int change_color(bst_t *tree_root, bst_t *parent);

/* Main function */
int main(void)
{
    int color;
    bst_t *root = NULL;
    bst_t *dred_root = NULL, *dred_parent = NULL;
	int function, data, element, idx, option, ret_val;

    while (1)
	{
		/* prompt functions */
		printf("Select any function\n");
		printf("01 - Insert node\n");
		printf("02 - Find max\n");
		printf("03 - Find min\n");
		printf("04 - Print in_order\n");
		printf("05 - Print pre_order\n");
		printf("06 - Print post_order\n");
		printf("07 - Find element\n");
		printf("08 - Delete node\n");
		printf("09 - find height\n");
		printf("10 - find no of nodes\n");
		printf("11 - rotate right\n");
		printf("12 - rotate left\n");
		printf("13 - find red red\n");
		printf("14 - resolve red red\n");
		printf("15 - exit\n");
		printf("16 - insert 0 - 65535\n");
		printf("17 - insert with color\n");
		printf("Function [1-17] ? : ");
		scanf("%d", &function);

		/* Invoking functions */
		switch (function)
		{
			case 1:
                printf("Enter the data : ");
                scanf("%d", &data);
                if (root == NULL)
                    color = black;
                else
                    color = red;
                root = insert_node(root, data, color);
                if (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) != FOUND)
                {
                    printf("\nDouble red condition not found\n\n");
                }
                else
                {
                    while (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) == FOUND)
                    {
                        printf("\nDouble red condition found\n");
                        resolve_doublered(&root, dred_root, dred_parent);
                        printf("Double red condition resolved\n\n");
                    }
                }
				break;
			case 2:
				find_max(root);
				break;
			case 3:
                find_min(root);
				break;
			case 4:
                printf("\n");
                print_in_order(root);
                printf("\n\n");
				break;
			case 5:
                printf("\n");
                print_pre_order(root);
                printf("\n\n");
				break;
			case 6:
                printf("\n");
                print_post_order(root);
                printf("\n\n");
				break;
			case 7:
				printf("Enter the element : ");
				scanf("%d", &element);
                find_element(root, element);
				break;
			case 8:
				printf("Enter the element : ");
				scanf("%d", &element);
                //root = delete_node(&root, root, NULL, element);
                delete_node1(&root, root, NULL, element);
				break;
			case 9:
                printf("\nHeight = %d\n\n", height_of_tree(root));
				break;
			case 10:
                printf("No of nodes = %d\n", count_node(root));
				break;
			case 11:
				printf("Enter the data : ");
				scanf("%d", &data);
                root = rotate_right(&root, root, NULL, data, 0);
                break;
			case 12:
				printf("Enter the data : ");
				scanf("%d", &data);
                root = rotate_left(&root, root, NULL, data, 0);
                break;
			case 13:
                dred_root = NULL;
                dred_parent = NULL;
                if (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) == FOUND)
                    printf("Double red condition found\n");
                else
                    printf("Double red condition not found\n");
                break;
			case 14:
                resolve_doublered(&root, dred_root, dred_parent);
                break;
			case 15:
                return 0;
			case 16:
                for (idx = 0; idx < 65536; idx++)
                {
                    data = idx;
                    if (root == NULL)
                        color = black;
                    else
                        color = red;
                    root = insert_node(root, data, color);
                    if (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) != FOUND)
                    {
                        printf("\nDouble red condition not found\n\n");
                    }
                    else
                    {
                        while (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) == FOUND)
                        {
                            printf("\nDouble red condition found\n");
                            resolve_doublered(&root, dred_root, dred_parent);
                            printf("Double red condition resolved\n\n");
                        }
                    }
                }
				break;
			case 17:
                printf("Enter the data : ");
                scanf("%d", &data);
                printf("Enter the color : ");
                scanf("%d", &color);
                root = insert_node(root, data, color);
                if (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) != FOUND)
                {
                    printf("\nDouble red condition not found\n\n");
                }
                else
                {
                    while (find_double_red(root, NULL, &dred_root, &dred_parent, NOT_FOUND) == FOUND)
                    {
                        printf("\nDouble red condition found\n");
                        resolve_doublered(&root, dred_root, dred_parent);
                        printf("Double red condition resolved\n\n");
                    }
                }
				break;
		}

	}
}

/* Create a node */
bst_t *create_node(int data, color_t color)
{
    bst_t *root = (bst_t *)malloc(sizeof(bst_t));
    root->data = data;
    root->color = color;
    root->left = NULL;
    root->right = NULL;

    return root;
}

/* Insert a node in binary search tree */
bst_t *insert_node(bst_t *root, int data, color_t color)
{
    if (root == NULL)
    {
        root = create_node(data, color);
        return root;
    }
    
    if (root->data > data)
    {
        root->left = insert_node(root->left, data, color);
    }
    else if(root->data < data)
    {
        root->right = insert_node(root->right, data, color);
    }
    else
    {
        printf("ERROR : Data already exists\n");
    }
    return root;
}

/* Find minimum value of in binary search tree */
int find_min(bst_t *root)
{
    if (root->left != NULL)
    {
         return find_min(root->left);
    }
    else
    {
        printf("%d\n", root->data);
        return root->data;
    }
}

/* Find maximum value of in binary search tree */
int find_max(bst_t *root)
{
    if (root->right != NULL)
    {
         return find_max(root->right);
    }
    else
    {
        printf("%d\n", root->data);
    }
    return root->data;
}

/* Print in order */
void print_in_order(bst_t *root)
{
    if (root != NULL)
    {
        print_in_order(root->left);
        if (root->color == black)
            printf("black ");
        else if (root->color == red)
            printf("red ");
        else
            printf("double_black ");
        printf("%d ", root->data);
        print_in_order(root->right);
    }
    return;
}

/* Print in pre-order */
void print_pre_order(bst_t *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        print_pre_order(root->left);
        print_pre_order(root->right);
    }
    return;
}

/* Print in post-order */
void print_post_order(bst_t *root)
{
    if (root != NULL)
    {
        print_post_order(root->left);
        print_post_order(root->right);
        printf("%d ", root->data);
    }
    return;
}

/* Find element in binary search tree */
bst_t *find_element(bst_t *root, int element)
{
    if (root == NULL)
    {
        printf("Element not found\n");
        return NULL;
    }
    
    if (root->data > element)
    {
        find_element(root->left, element);
    }
    else if(root->data < element)
    {
        find_element(root->right, element);
    }
    else if(root->data == element)
    {
        printf("%d\n", root->data);
        return root;
    }
}

/* To delete a node */
bst_t *delete_node(bst_t **tree_root, bst_t *root, bst_t *parent, int element)
{
    bst_t *temp;
    int successor;
    bst_t *sibling;
    bst_t *l_child, r_child;

    /* If element not found */
    if (root == NULL)
    {
        printf("Element not present\n");
        return root;
    }

    /* If element is present in right side */
    if (element > root->data)
    {
        root->right = delete_node(tree_root, root->right, root, element);
        return root;
    }

    /* If element is present in left side */
    else if (element < root->data)
    {
        root->left = delete_node(tree_root, root->left, root, element);
        return root;
    }

    /* If element is present */
    /* If the element has single child and in left or leaf*/
    if (root->color == red)
    {
        if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /* If the element has single child and in right or leaf */
        else if(root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        /* If the element has two child  */
           successor = find_min(root->right);
           root->data = successor;

        /* To delete that successor node */
           root->right = delete_node(tree_root, root->right, root, successor);
           return root;
    }
    else if (root->color == black)
    {
        /* Double black case */
        if (root->left == NULL && root->right == NULL)
        {
            /* If only root is present and is to be deleted */
            if (parent == NULL)
            {
                free(root);
                return NULL;
            }
            /* Case - 4*/
            if (parent->left == root && parent->color == red)
                if (parent->right != NULL && parent->right->color == black)
                    if(parent->right->left != NULL && parent->right->left->color == black && parent->right->right != NULL && parent->right->right->color == black)
                    {
                        printf("case - 4 - 1\n");
                        parent->color = black;
                        parent->right->color = red;
                        free(root);
                        return NULL;
                    }
            else if (parent->right == root && parent->color == red)
                    if (parent->left != NULL && parent->left->color == black)
                        if(parent->left->left != NULL && parent->left->left->color == black && parent->left->right != NULL && parent->left->right->color == black)
                    {
                        printf("case - 4 - 2\n");
                        parent->color = black;
                        parent->left->color = red;
                        free(root);
                        return NULL;
                    }
            /* Case - 6*/
            if (parent->left == root && parent->right != NULL && parent->right->color == black)
                if (parent->right->right != NULL && parent->right->right->color == red)
                {
                    printf("case - 6 - 1\n");
                    parent->right->right->color = black;
                    parent->right->color = parent->color;
                    parent->color = red;
                    free(root);
                    parent->left == NULL;
                    rotate_left(tree_root, *tree_root, NULL, parent->data, DO_NOT_SWAP_COLOR);
                    (*tree_root)->color = black;
                    return NULL;
                }
                else if (parent->right == root && parent->left != NULL && parent->left->color == black)
                    if(parent->left->left != NULL && parent->left->left->color ==red)
                    {
                        printf("case - 6 - 2\n");
                        parent->left->left->color = black;
                        parent->left->color = parent->color;
                        parent->color = red;
                        free(root);
                        parent->right == NULL;
                        rotate_right(tree_root, *tree_root, NULL, parent->data, DO_NOT_SWAP_COLOR);
                        (*tree_root)->color = black;
                        return NULL;
                    }
        }

        if (root->right == NULL)
        {
            temp = root->left;
            temp->color = root->color;
            free(root);
            return temp;
        }

        /* If the element has single child and in right or leaf */
        else if(root->left == NULL)
        {
            temp = root->right;
            temp->color = root->color;
            free(root);
            return temp;
        }

        /* If the element has two child  */
        successor = find_min(root->right);
        root->data = successor;

        /* To delete that successor node */
        root->right = delete_node(tree_root, root->right, root, successor);

        return root;
    }
}

/* To delete a node */
int delete_node1(bst_t **tree_root, bst_t *root, bst_t *parent, int element)
{
    bst_t *temp;
    int successor;
    bst_t *sibling;
    bst_t *l_child, r_child;

    /* If element not found */
    if (root == NULL)
    {
        printf("Element not present\n");
        return 0;
    }

    /* If element is present in right side */
    if (element > root->data)
    {
        delete_node1(tree_root, root->right, root, element);
        return 0;
    }

    /* If element is present in left side */
    else if (element < root->data)
    {
        delete_node1(tree_root, root->left, root, element);
        return 0;
    }

    /* If element is present */
    /* If the element has single child and in left or leaf*/
    if (root->color == red)
    {
        if (root->right == NULL)
        {
            if (*tree_root == root)
            {
                *tree_root = root->left;
            }
            else
            {
                if (parent->left == root)
                    parent->left = root->left;
                else
                    parent->right = root->left;
            }
            free(root);
            return 0;
        }

        /* If the element has single child and in right or leaf */
        else if(root->left == NULL)
        {
            if (*tree_root == root)
            {
                *tree_root = root->right;
            }
            else
            {
                if (parent->left == root)
                    parent->left = root->right;
                else
                    parent->right = root->right;
            }
            free(root);
            return 0;
        }

        /* If the element has two child  */
           successor = find_min(root->right);
           root->data = successor;

        /* To delete that successor node */
           delete_node1(tree_root, root->right, root, successor);
           return 0;
    }
    else if (root->color == black)
    {
        printf("Node to be deleted is black\n");
        /* Double black case */
        if (root->left == NULL && root->right == NULL)
        {
            /* If only root is present and is to be deleted */
            if (parent == NULL)
            {
                free(root);
                *tree_root = NULL;
                return 0;
            }

            /* Case - 2*/
            if (parent->left == root && parent->color == black)
                if (parent->right != NULL && parent->right->color == red)
                    if(parent->right->left != NULL && parent->right->left->color == black && parent->right->right != NULL && parent->right->right->color == black)
                    {
                        printf("case - 2 - 1 - 1\n");
                        root->color = double_black;
                        rotate_left(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                        (*tree_root)->color = black;
                        delete_node1(tree_root, *tree_root, NULL, root->data);
                        return 0;
                    }
                    else if (parent->right->left == NULL && parent->right->right == NULL)
                    {
                        printf("case - 2 - 1 - 2\n");
                        root->color = double_black;
                        rotate_left(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                        (*tree_root)->color = black;
                        delete_node1(tree_root, *tree_root, NULL, root->data);
                        return 0;
                    }
            else if (parent->right == root && parent->color == black)
                    if (parent->left != NULL && parent->left->color == red)
                        if(parent->left->left != NULL && parent->left->left->color == black && parent->left->right != NULL && parent->left->right->color == black)
                    {
                        printf("case - 2 - 2 - 1\n");
                        root->color = double_black;
                        rotate_right(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                        (*tree_root)->color = black;
                        delete_node1(tree_root, *tree_root, NULL, root->data);
                        return 0;
                    }
                    else if (parent->left->left == NULL && parent->left->right == NULL)
                    {
                        printf("case - 2 - 2 - 2\n");
                        root->color = double_black;
                        rotate_right(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                        (*tree_root)->color = black;
                        delete_node1(tree_root, *tree_root, NULL, root->data);
                        return 0;
                    }
            /* Case - 3*/
            if (parent->left == root && parent->color == black)
                if (parent->right != NULL && parent->right->color == black)
                    if(parent->right->left != NULL && parent->right->left->color == black && parent->right->right != NULL && parent->right->right->color == black)
                    {
                        printf("case - 3 - 1 - 1\n");
                        parent->right->color = red;
                        free(root);
                        parent->left = NULL;
                        parent->color = double_black;
                        delete_node1(tree_root, *tree_root, NULL, parent->data);
                        return 0;
                    }
                    else if (parent->right->left == NULL && parent->right->right == NULL)
                    {
                        printf("case - 3 - 1 - 2\n");
                        parent->right->color = red;
                        free(root);
                        parent->left = NULL;
                        parent->color = double_black;
                        delete_node1(tree_root, *tree_root, NULL, parent->data);
                        return 0;
                    }
            else if (parent->right == root && parent->color == black)
                    if (parent->left != NULL && parent->left->color == black)
                        if(parent->left->left != NULL && parent->left->left->color == black && parent->left->right != NULL && parent->left->right->color == black)
                    {
                        printf("case - 3 - 2 - 1\n");
                        parent->left->color = red;
                        free(root);
                        parent->right = NULL;
                        parent->color = double_black;
                        delete_node1(tree_root, *tree_root, NULL, parent->data);
                        return 0;
                    }
                    else if (parent->left->left == NULL && parent->left->right == NULL)
                    {
                        printf("case - 3 - 2 - 2\n");
                        parent->left->color = red;
                        free(root);
                        parent->left = NULL;
                        parent->color = double_black;
                        delete_node1(tree_root, *tree_root, NULL, parent->data);
                        return 0;
                    }

            /* Case - 4*/
            if (parent->left == root && parent->color == red)
                if (parent->right != NULL && parent->right->color == black)
                    if(parent->right->left != NULL && parent->right->left->color == black && parent->right->right != NULL && parent->right->right->color == black)
                    {
                        printf("case - 4 - 1 - 1\n");
                        parent->color = black;
                        parent->right->color = red;
                        free(root);
                        parent->left = NULL;
                        return 0;
                    }
                    else if (parent->right->left == NULL && parent->right->right == NULL)
                    {
                        printf("case - 4 - 1 - 2\n");
                        parent->color = black;
                        parent->right->color = red;
                        free(root);
                        parent->left = NULL;
                        return 0;
                    }
            else if (parent->right == root && parent->color == red)
                    if (parent->left != NULL && parent->left->color == black)
                        if(parent->left->left != NULL && parent->left->left->color == black && parent->left->right != NULL && parent->left->right->color == black)
                    {
                        printf("case - 4 - 2 - 1\n");
                        parent->color = black;
                        parent->left->color = red;
                        free(root);
                        parent->right = NULL;
                        return 0;
                    }
                    else if (parent->left->left == NULL && parent->left->right == NULL)
                    {
                        printf("case - 4 - 2 - 2\n");
                        parent->color = black;
                        parent->left->color = red;
                        free(root);
                        parent->left = NULL;
                        return 0;
                    }
            

            /* Case - 6*/
            if (parent->left == root && parent->right != NULL && parent->right->color == black)
                if (parent->right->right != NULL && parent->right->right->color == red)
                {
                    printf("case - 6 - 1\n");
                    parent->right->right->color = black;
                    parent->right->color = parent->color;
                    parent->color = black;
                    free(root);
                    parent->left = NULL;
                    rotate_left(tree_root, *tree_root, NULL, parent->data, DO_NOT_SWAP_COLOR);
                    (*tree_root)->color = black;
                    return 0;
                }
                else if (parent->right == root && parent->left != NULL && parent->left->color == black)
                    if(parent->left->left != NULL && parent->left->left->color ==red)
                    {
                        printf("case - 6 - 2\n");
                        parent->left->left->color = black;
                        parent->left->color = parent->color;
                        parent->color = black;
                        free(root);
                        parent->right = NULL;
                        rotate_right(tree_root, *tree_root, NULL, parent->data, DO_NOT_SWAP_COLOR);
                        (*tree_root)->color = black;
                        return 0;
                    }
        }

        else if (root->right == NULL)
        {
            if (*tree_root == root)
            {
                *tree_root = root->left;
                (*tree_root)->color = black;
            }
            else
            {
                if (parent->left == root)
                {
                    parent->left = root->left;
                    parent->color = root->color;
                }
                else
                {
                    parent->right = root->left;
                    parent->color = root->color;
                }
            }
            free(root);
            return 0;
        }

        /* If the element has single child and in right or leaf */
        else if(root->left == NULL)
        {
            if (*tree_root == root)
            {
                *tree_root = root->right;
                (*tree_root)->color = black;
            }
            else
            {
                if (parent->left == root)
                {
                    parent->left = root->right;
                    parent->color = root->color;
                }
                else
                {
                    parent->right = root->right;
                    parent->color = root->color;
                }
            }
            free(root);
            return 0;
        }

        /* If the element has two child  */
        successor = find_min(root->right);
        root->data = successor;

        /* To delete that successor node */
        delete_node1(tree_root, root->right, root, successor);

        return 0;
    }
    else if (root->color == double_black)
    {
        printf("Double black from propogating condition\n");
        /* Case 1 */
        if (root->data == (*tree_root)->data)
        {
            printf("case 1\n");
            (*tree_root)->color = black;
            return 0;
        }

        /* Case - 4*/
        if (parent->left == root && parent->color == red)
            if (parent->right != NULL && parent->right->color == black)
                if(parent->right->left != NULL && parent->right->left->color == black && parent->right->right != NULL && parent->right->right->color == black)
                {
                    printf("case - 4 - 1 - 1\n");
                    parent->color = black;
                    parent->right->color = red;
                    free(root);
                    parent->left = NULL;
                    return 0;
                }
                else if (parent->right->left == NULL && parent->right->right == NULL)
                {
                    printf("case - 4 - 1 - 2\n");
                    parent->color = black;
                    parent->right->color = red;
                    free(root);
                    parent->left = NULL;
                    return 0;
                }
                else if (parent->right == root && parent->color == red)
                    if (parent->left != NULL && parent->left->color == black)
                        if(parent->left->left != NULL && parent->left->left->color == black && parent->left->right != NULL && parent->left->right->color == black)
                        {
                            printf("case - 4 - 2 - 1\n");
                            parent->color = black;
                            parent->left->color = red;
                            free(root);
                            parent->right = NULL;
                            return 0;
                        }
                        else if (parent->left->left == NULL && parent->left->right == NULL)
                        {
                            printf("case - 4 - 2 - 2\n");
                            parent->color = black;
                            parent->left->color = red;
                            free(root);
                            parent->left = NULL;
                            return 0;
                        }

        /* case 5 */
        if (parent->left == root && parent->color == black)
            if (parent->right != NULL && parent->right->color == black)
                if(parent->right->left != NULL && parent->right->left->color == red && parent->right->right != NULL && parent->right->right->color == black)
                {
                    printf("case - 5 - 1 - 1\n");
                    rotate_right(tree_root, *tree_root, NULL, parent->right->data, SWAP_COLOR);
                    (*tree_root)->color = black;
                    delete_node1(tree_root, *tree_root, NULL, root->data);
                    return 0;
                }
        else if (parent->right == root && parent->color == black)
                if (parent->left != NULL && parent->left->color == black)
                    if(parent->left->left != NULL && parent->left->left->color == black && parent->left->right != NULL && parent->left->right->color == red)
                {
                    printf("case - 5 - 2 - 1\n");
                    rotate_left(tree_root, *tree_root, NULL, parent->right->data, SWAP_COLOR);
                    (*tree_root)->color = black;
                    delete_node1(tree_root, *tree_root, NULL, root->data);
                    return 0;
                }

            /* Case - 6*/
        if (parent->left == root && parent->right != NULL && parent->right->color == black)
            if (parent->right->right != NULL && parent->right->right->color == red)
            {
                printf("case - 6 - 1\n");
                parent->right->right->color = black;
                parent->right->color = parent->color;
                parent->color = black;
                rotate_left(tree_root, *tree_root, NULL, parent->data, DO_NOT_SWAP_COLOR);
                (*tree_root)->color = black;
                root->color = black;
                return 0;
            }
            else if (parent->right == root && parent->left != NULL && parent->left->color == black)
                if(parent->left->left != NULL && parent->left->left->color ==red)
                {
                    printf("case - 6 - 2\n");
                    parent->left->left->color = black;
                    parent->left->color = parent->color;
                    parent->color = black;
                    rotate_right(tree_root, *tree_root, NULL, parent->data, DO_NOT_SWAP_COLOR);
                    (*tree_root)->color = black;
                    root->color = black;
                    return 0;
                }
    }
}

/*Function for height of a tree*/
int height_of_tree(bst_t *node)
{
    int left_depth, right_depth;

    if (node == NULL) 
    {
	    return 0;
    }
    else
    {
        left_depth = height_of_tree(node->left);
        right_depth = height_of_tree(node->right);

        if (left_depth > right_depth) 
        {
            return(left_depth+1);
        }
        else
        {
            return(right_depth+1);
        }
    }
}

/*Function for finding number of nodes*/
int count_node(bst_t *root)
{
    int count = 1;

    if (root == NULL)
    {
	    return 0;
    }
    else
    {
        count += count_node(root->left);
        count += count_node(root->right);
	    return count;
    }
}

bst_t *rotate_right(bst_t **tree_root, bst_t *root, bst_t *parent, int data, int swap_color)
{
    bst_t *ptr;
    color_t temp;

    if (root == NULL)
    {
        return root;
    }
    else
    {
        if (data < root->data)
        {
            root->left = rotate_right(tree_root, root->left, root, data, swap_color);
            return root;
        }
        else if (data > root->data)
        {
            root->right = rotate_right(tree_root, root->right, root, data, swap_color);
            return root;
        }
        else
        {
            ptr = root->left;
            root->left = ptr->right;
            if (parent == NULL)
            {
                *tree_root = ptr;
            }
            else if (parent->left == root)
            {
                parent->left = ptr;
            }
            else if (parent->right == root)
            {
                parent->right = ptr;
            }
            ptr->right = root;
            if (swap_color)
            {
                temp = ptr->color;
                ptr->color = root->color;
                root->color = temp;
                /* Maintaining root color black */
                (*tree_root)->color = black;
            }
            return ptr;
        }
    }
}

bst_t *rotate_left(bst_t **tree_root, bst_t *root, bst_t *parent, int data, int swap_color)
{
    bst_t *ptr;
    color_t temp;

    if (root == NULL)
    {
        return root;
    }
    else
    {
        if (data < root->data)
        {
            root->left = rotate_left(tree_root, root->left, root, data, swap_color);
            return root;
        }
        else if (data > root->data)
        {
            root->right = rotate_left(tree_root, root->right, root, data, swap_color);
            return root;
        }
        else
        {
            ptr = root->right;
            root->right = ptr->left;
            if (parent == NULL)
            {
                *tree_root = ptr;
            }
            else if (parent->left == root)
            {
                parent->left = ptr;
            }
            else if (parent->right == root)
            {
                parent->right = ptr;
            }
            ptr->left = root;
            if (swap_color)
            {
                temp = ptr->color;
                ptr->color = root->color;
                root->color = temp;
                (*tree_root)->color = black;
            }
            return ptr;
        }
    }
}

int find_double_red(bst_t *root, bst_t *parent, bst_t **dred_root, bst_t **dred_parent, int double_red)
{
    if (root != NULL)
    {
        double_red = find_double_red(root->left, root, dred_root, dred_parent, double_red);

        /* Stop recursive calling if double red condiion if found */
        if (double_red == NOT_FOUND)
        {
            /* Left child is not NULL */
            /* Root color and left child color is red */
            if (root->left != NULL && root->color == red && root->left->color == red)
            {
                *dred_root = root;
                *dred_parent = parent;
                return (double_red = FOUND);
            }

            /* Right child is not NULL */
            /* Root color and right child color is red */
            if (root->right != NULL && root->color == red && root->right->color == red)
            {
                *dred_root = root;
                *dred_parent = parent;
                return (double_red = FOUND);
            }

            double_red = find_double_red(root->right, root, dred_root, dred_parent, double_red);
        }
    }
    return double_red;
}

int resolve_doublered(bst_t **tree_root, bst_t *root, bst_t *parent)
{
    int rotation_type = -1;
    int flag = 0;

        /*****************************************************************/
        /* Root is left child of parent and right child of parent is red */
        if (parent->left == root && parent->right != NULL && parent->right->color == red)
        {
            puts("double red with right sibling red");
            change_color(*tree_root, parent);
        }

        /* Root is right child of parent and left child of parent is red */
        else if (parent->right == root && parent->left != NULL && parent->left->color == red)
        {
            puts("double red with sibling left red");
            change_color(*tree_root, parent);
        }

        /* Root is left child of parent and right child of parent is NULL */
        else if (parent->left == root && (parent->right == NULL || parent->right->color == black))
        {
            puts("double red with right sibling black or null");
            flag = 1;
        }

        /* Root is right child of parent and left child of parent is NULL */
        else if (parent->right == root && (parent->left == NULL || parent->left->color == black))
        {
            puts("double red with left sibling black or null");
            flag = 1;
        }
        /*****************************************************************/

        if (flag)
        {
            rotation_type = get_rotation_type(root, parent);

            switch(rotation_type)
            {
                case 0:
                    printf("right rotation at %d\n", parent->data);
                    rotate_right(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                    break;
                case 1:
                    printf("right rotation at %d\n", root->data);
                    rotate_right(tree_root, *tree_root, NULL, root->data, DO_NOT_SWAP_COLOR);

                    printf("left rotation at %d\n", parent->data);
                    rotate_left(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                    break;
                case 2:
                    printf("left rotation at %d\n", root->data);
                    rotate_left(tree_root, *tree_root, NULL, root->data, DO_NOT_SWAP_COLOR);

                    printf("right rotation at %d\n", parent->data);
                    rotate_right(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                    break;
                case 3:
                    printf("left rotation at %d\n", parent->data);
                    rotate_left(tree_root, *tree_root, NULL, parent->data, SWAP_COLOR);
                    break;
            }
        }

    return 0;
}

int change_color(bst_t *tree_root, bst_t *parent)
{
    printf("changing color at parent %d\n", parent->data);
    if (parent != tree_root)
    if (parent->color == red)
    {
        parent->color = black;
    }
    else
    {
        parent->color = red;
    }

    /* Change color of left child */
    if (parent->left != NULL)
    {
        if  (parent->left->color == red)
        {
            parent->left->color = black;
        }
        else
        {
            parent->left->color = red;
        }
    }

    /* Change color of right child */
    if (parent->right != NULL)
    {
        if (parent->right->color == red)
        {
            parent->right->color = black;
        }
        else
        {
            parent->right->color = red;
        }
    }
    return 0;
}

int get_rotation_type(bst_t *root, bst_t *parent)
{
    int root_pos = 0;
    int child_pos = 0;

    /* If root is left child of parent */
    if (parent->left == root)
        root_pos = LEFT;
    else
        root_pos = RIGHT;

    /* If child is left child of root */
    if (root->left != NULL && root->color == red && root->left->color == red)
        child_pos = LEFT;
    else
        child_pos = RIGHT;

    /* Decide rotation type */
    switch(child_pos)
    {
        case LEFT:
            switch(root_pos)
            {
                case LEFT:
                    return 0;
                case RIGHT:
                    return 1;
            }

        case RIGHT:
            switch(root_pos)
            {
                case LEFT:
                    return 2;
                case RIGHT:
                    return 3;
            }
    }
}
