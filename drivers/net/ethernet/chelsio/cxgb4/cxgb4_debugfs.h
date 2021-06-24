<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __CXGB4_DEBUGFS_H
#घोषणा __CXGB4_DEBUGFS_H

#समावेश <linux/export.h>

काष्ठा t4_debugfs_entry अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *ops;
	umode_t mode;
	अचिन्हित अक्षर data;
पूर्ण;

काष्ठा seq_tab अणु
	पूर्णांक (*show)(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx);
	अचिन्हित पूर्णांक rows;        /* # of entries */
	अचिन्हित अक्षर width;      /* size in bytes of each entry */
	अचिन्हित अक्षर skip_first; /* whether the first line is a header */
	अक्षर data[];             /* the table data */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक hex2val(अक्षर c)
अणु
	वापस है_अंक(c) ? c - '0' : tolower(c) - 'a' + 10;
पूर्ण

काष्ठा seq_tab *seq_खोलो_tab(काष्ठा file *f, अचिन्हित पूर्णांक rows,
			     अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक have_header,
			     पूर्णांक (*show)(काष्ठा seq_file *seq, व्योम *v, पूर्णांक i));

पूर्णांक t4_setup_debugfs(काष्ठा adapter *adap);
व्योम add_debugfs_files(काष्ठा adapter *adap,
		       काष्ठा t4_debugfs_entry *files,
		       अचिन्हित पूर्णांक nfiles);
पूर्णांक mem_खोलो(काष्ठा inode *inode, काष्ठा file *file);

#पूर्ण_अगर
