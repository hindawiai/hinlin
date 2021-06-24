<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * call-path.h: Manipulate a tree data काष्ठाure containing function call paths
 * Copyright (c) 2014, Intel Corporation.
 */

#अगर_अघोषित __PERF_CALL_PATH_H
#घोषणा __PERF_CALL_PATH_H

#समावेश <sys/types.h>

#समावेश <linux/types.h>
#समावेश <linux/rbtree.h>

/**
 * काष्ठा call_path - node in list of calls leading to a function call.
 * @parent: call path to the parent function call
 * @sym: symbol of function called
 * @ip: only अगर sym is null, the ip of the function
 * @db_id: id used क्रम db-export
 * @in_kernel: whether function is a in the kernel
 * @rb_node: node in parent's tree of called functions
 * @children: tree of call paths of functions called
 *
 * In combination with the call_वापस काष्ठाure, the call_path काष्ठाure
 * defines a context-sensitive call-graph.
 */
काष्ठा call_path अणु
	काष्ठा call_path *parent;
	काष्ठा symbol *sym;
	u64 ip;
	u64 db_id;
	bool in_kernel;
	काष्ठा rb_node rb_node;
	काष्ठा rb_root children;
पूर्ण;

#घोषणा CALL_PATH_BLOCK_SHIFT 8
#घोषणा CALL_PATH_BLOCK_SIZE (1 << CALL_PATH_BLOCK_SHIFT)
#घोषणा CALL_PATH_BLOCK_MASK (CALL_PATH_BLOCK_SIZE - 1)

काष्ठा call_path_block अणु
	काष्ठा call_path cp[CALL_PATH_BLOCK_SIZE];
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा call_path_root - root of all call paths.
 * @call_path: root call path
 * @blocks: list of blocks to store call paths
 * @next: next मुक्त space
 * @sz: number of spaces
 */
काष्ठा call_path_root अणु
	काष्ठा call_path call_path;
	काष्ठा list_head blocks;
	माप_प्रकार next;
	माप_प्रकार sz;
पूर्ण;

काष्ठा call_path_root *call_path_root__new(व्योम);
व्योम call_path_root__मुक्त(काष्ठा call_path_root *cpr);

काष्ठा call_path *call_path__findnew(काष्ठा call_path_root *cpr,
				     काष्ठा call_path *parent,
				     काष्ठा symbol *sym, u64 ip, u64 ks);

#पूर्ण_अगर
