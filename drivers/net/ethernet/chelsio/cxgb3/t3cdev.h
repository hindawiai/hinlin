<शैली गुरु>
/*
 * Copyright (C) 2006-2008 Chelsio Communications.  All rights reserved.
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
#अगर_अघोषित _T3CDEV_H_
#घोषणा _T3CDEV_H_

#समावेश <linux/list.h>
#समावेश <linux/atomic.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <net/neighbour.h>

#घोषणा T3CNAMSIZ 16

काष्ठा cxgb3_client;

क्रमागत t3ctype अणु
	T3A = 0,
	T3B,
	T3C,
पूर्ण;

काष्ठा t3cdev अणु
	अक्षर name[T3CNAMSIZ];	/* T3C device name */
	क्रमागत t3ctype type;
	काष्ठा list_head ofld_dev_list;	/* क्रम list linking */
	काष्ठा net_device *lldev;	/* LL dev associated with T3C messages */
	काष्ठा proc_dir_entry *proc_dir;	/* root of proc dir क्रम this T3C */
	पूर्णांक (*send)(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb);
	पूर्णांक (*recv)(काष्ठा t3cdev *dev, काष्ठा sk_buff **skb, पूर्णांक n);
	पूर्णांक (*ctl)(काष्ठा t3cdev *dev, अचिन्हित पूर्णांक req, व्योम *data);
	व्योम (*neigh_update)(काष्ठा t3cdev *dev, काष्ठा neighbour *neigh);
	व्योम *priv;		/* driver निजी data */
	व्योम __rcu *l2opt;	/* optional layer 2 data */
	व्योम *l3opt;		/* optional layer 3 data */
	व्योम *l4opt;		/* optional layer 4 data */
	व्योम *ulp;		/* ulp stuff */
	व्योम *ulp_iscsi;	/* ulp iscsi */
पूर्ण;

#पूर्ण_अगर				/* _T3CDEV_H_ */
