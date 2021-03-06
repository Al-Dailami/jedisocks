/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
 *  Modified by jedihy
 *  This original files are part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/

#ifndef _C_MAP_H_
#define _C_MAP_H_

#include <stdlib.h>
// MACROS handling exceptions
/* ------------------------------------------------------------------------*/
/*                 C O M M O N    E R R O R    C O D E                     */
/* ------------------------------------------------------------------------*/
#define CLIB_ERROR_SUCCESS  0
#define CLIB_ERROR_ERROR    1
#define CLIB_ERROR_MEMORY   2
#define CLIB_ELEMENT_RETURN_ERROR 3
/* ------------------------------------------------------------------------*/
/*         D Y N A M I C    A R R A Y   E R R O R    C O D E S             */
/* ------------------------------------------------------------------------*/
#define CLIB_ARRAY_NOT_INITIALIZED    101
#define CLIB_ARRAY_INDEX_OUT_OF_BOUND 102
#define CLIB_ARRAY_INSERT_FAILED      103

#define CLIB_DEQUE_NOT_INITIALIZED    201
#define CLIB_DEQUE_INDEX_OUT_OF_BOUND 202

#define CLIB_RBTREE_NOT_INITIALIZED   401
#define CLIB_RBTREE_KEY_DUPLICATE     401
#define CLIB_RBTREE_KEY_NOT_FOUND     402

#define CLIB_SET_NOT_INITIALIZED      501
#define CLIB_SET_INVALID_INPUT        502

#define CLIB_MAP_NOT_INITIALIZED      501
#define CLIB_MAP_INVALID_INPUT        502

#define CLIB_SLIST_INSERT_FAILED      601


// parent class objs and funcs definitions
/* ------------------------------------------------------------------------*/
/*       C O M M O N       D E F I N I T O N S                             */
/* ------------------------------------------------------------------------*/

typedef void (*clib_destroy)(void*);
typedef int  (*clib_compare)(void*,void*);
typedef void (*clib_traversal)( void*);

typedef int  clib_error;
typedef int  clib_bool;

#define clib_black           0
#define clib_red             1
#define clib_true            1
#define clib_false           0

/* ------------------------------------------------------------------------*/
/*                            P  A  I   R                                  */
/* ------------------------------------------------------------------------*/

struct clib_object {
    void* raw_data;
    size_t size;
};

struct clib_iterator {
	struct clib_object* (*get_next)(struct clib_iterator*);
	void (*replace_value)(struct clib_iterator*,void*,size_t);
	void* (*get_value)(void*);
	void* pContainer;
	int   pCurrent;
	void* pCurrentElement;
};

/* ------------------------------------------------------------------------*/
/*            H E L P E R       F U N C T I O N S                          */
/* ------------------------------------------------------------------------*/

extern void  clib_copy ( void* destination, void* source, size_t size );
extern void  clib_get  ( void* destination, void* source, size_t size);
extern char* clib_strdup ( char *ptr );

extern struct clib_object* new_clib_object (void* inObject, size_t obj_size);
extern clib_error get_raw_clib_object (struct clib_object *inObject, void**elem);
extern void  delete_clib_object  (struct clib_object* inObject );
extern void replace_raw_clib_object(struct clib_object* current_object,void* elem, size_t elem_size);


// rbtree structure start
struct clib_rb_node {
    struct clib_rb_node *left;
    struct clib_rb_node *right;
    struct clib_rb_node *parent;
    int color; 
    struct clib_object* key;
    struct clib_object* value; 
};

struct clib_rb {
    struct clib_rb_node* root;
    struct clib_rb_node sentinel;
    clib_destroy destruct_k_fn;
	clib_destroy destruct_v_fn;
    clib_compare compare_fn;
};

extern struct clib_rb* new_c_rb(clib_compare fn_c,clib_destroy fn_ed, clib_destroy fn_vd );
extern clib_error  insert_c_rb(struct clib_rb* pTree, void* key, size_t key_size, void* value, size_t value_size);
extern struct clib_rb_node*   find_c_rb (struct clib_rb* pTree, void* key);
extern struct clib_rb_node* remove_c_rb (struct clib_rb* pTree, void* key);
extern clib_error  delete_c_rb (struct clib_rb* pTree);
extern clib_bool   empty_c_rb  (struct clib_rb* pTree);

extern struct clib_rb_node *minimum_c_rb( struct clib_rb* pTree, struct clib_rb_node* x );
extern struct clib_rb_node* tree_successor(struct clib_rb* pTree, struct clib_rb_node* x);
// rbtree structure end

struct clib_map {
    struct clib_rb* root;
};


extern struct clib_map* new_c_map    ( clib_compare fn_c_k, clib_destroy fn_k_d, clib_destroy fn_v_d);
extern clib_error   insert_c_map ( struct clib_map* pMap, void* key, size_t key_size, void* value,  size_t value_size);
extern clib_bool    exists_c_map ( struct clib_map* pMap, void* key);
extern clib_error   remove_c_map ( struct clib_map* pMap, void* key, void**value);
extern clib_bool    find_c_map   ( struct clib_map* pMap, void* key, void**value);
extern clib_error   delete_c_map ( struct clib_map* pMap);

extern struct clib_iterator* new_iterator_c_map(struct clib_map* pMap);
extern void delete_iterator_c_map ( struct clib_iterator* pItr);


#endif