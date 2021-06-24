<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
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

#समावेश <linux/err.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

काष्ठा file_operations;

#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>

#समावेश "ipoib.h"

अटल काष्ठा dentry *ipoib_root;

अटल व्योम क्रमmat_gid(जोड़ ib_gid *gid, अक्षर *buf)
अणु
	पूर्णांक i, n;

	क्रम (n = 0, i = 0; i < 8; ++i) अणु
		n += प्र_लिखो(buf + n, "%x",
			     be16_to_cpu(((__be16 *) gid->raw)[i]));
		अगर (i < 7)
			buf[n++] = ':';
	पूर्ण
पूर्ण

अटल व्योम *ipoib_mcg_seq_start(काष्ठा seq_file *file, loff_t *pos)
अणु
	काष्ठा ipoib_mcast_iter *iter;
	loff_t n = *pos;

	iter = ipoib_mcast_iter_init(file->निजी);
	अगर (!iter)
		वापस शून्य;

	जबतक (n--) अणु
		अगर (ipoib_mcast_iter_next(iter)) अणु
			kमुक्त(iter);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस iter;
पूर्ण

अटल व्योम *ipoib_mcg_seq_next(काष्ठा seq_file *file, व्योम *iter_ptr,
				   loff_t *pos)
अणु
	काष्ठा ipoib_mcast_iter *iter = iter_ptr;

	(*pos)++;

	अगर (ipoib_mcast_iter_next(iter)) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	वापस iter;
पूर्ण

अटल व्योम ipoib_mcg_seq_stop(काष्ठा seq_file *file, व्योम *iter_ptr)
अणु
	/* nothing क्रम now */
पूर्ण

अटल पूर्णांक ipoib_mcg_seq_show(काष्ठा seq_file *file, व्योम *iter_ptr)
अणु
	काष्ठा ipoib_mcast_iter *iter = iter_ptr;
	अक्षर gid_buf[माप "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"];
	जोड़ ib_gid mgid;
	अचिन्हित दीर्घ created;
	अचिन्हित पूर्णांक queuelen, complete, send_only;

	अगर (!iter)
		वापस 0;

	ipoib_mcast_iter_पढ़ो(iter, &mgid, &created, &queuelen,
			      &complete, &send_only);

	क्रमmat_gid(&mgid, gid_buf);

	seq_म_लिखो(file,
		   "GID: %s\n"
		   "  created: %10ld\n"
		   "  queuelen: %9d\n"
		   "  complete: %9s\n"
		   "  send_only: %8s\n"
		   "\n",
		   gid_buf, created, queuelen,
		   complete ? "yes" : "no",
		   send_only ? "yes" : "no");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ipoib_mcg_sops = अणु
	.start = ipoib_mcg_seq_start,
	.next  = ipoib_mcg_seq_next,
	.stop  = ipoib_mcg_seq_stop,
	.show  = ipoib_mcg_seq_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(ipoib_mcg);

अटल व्योम *ipoib_path_seq_start(काष्ठा seq_file *file, loff_t *pos)
अणु
	काष्ठा ipoib_path_iter *iter;
	loff_t n = *pos;

	iter = ipoib_path_iter_init(file->निजी);
	अगर (!iter)
		वापस शून्य;

	जबतक (n--) अणु
		अगर (ipoib_path_iter_next(iter)) अणु
			kमुक्त(iter);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस iter;
पूर्ण

अटल व्योम *ipoib_path_seq_next(काष्ठा seq_file *file, व्योम *iter_ptr,
				   loff_t *pos)
अणु
	काष्ठा ipoib_path_iter *iter = iter_ptr;

	(*pos)++;

	अगर (ipoib_path_iter_next(iter)) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	वापस iter;
पूर्ण

अटल व्योम ipoib_path_seq_stop(काष्ठा seq_file *file, व्योम *iter_ptr)
अणु
	/* nothing क्रम now */
पूर्ण

अटल पूर्णांक ipoib_path_seq_show(काष्ठा seq_file *file, व्योम *iter_ptr)
अणु
	काष्ठा ipoib_path_iter *iter = iter_ptr;
	अक्षर gid_buf[माप "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"];
	काष्ठा ipoib_path path;
	पूर्णांक rate;

	अगर (!iter)
		वापस 0;

	ipoib_path_iter_पढ़ो(iter, &path);

	क्रमmat_gid(&path.pathrec.dgid, gid_buf);

	seq_म_लिखो(file,
		   "GID: %s\n"
		   "  complete: %6s\n",
		   gid_buf, sa_path_get_dlid(&path.pathrec) ? "yes" : "no");

	अगर (sa_path_get_dlid(&path.pathrec)) अणु
		rate = ib_rate_to_mbps(path.pathrec.rate);

		seq_म_लिखो(file,
			   "  DLID:     0x%04x\n"
			   "  SL: %12d\n"
			   "  rate: %8d.%d Gb/sec\n",
			   be32_to_cpu(sa_path_get_dlid(&path.pathrec)),
			   path.pathrec.sl,
			   rate / 1000, rate % 1000);
	पूर्ण

	seq_अ_दो(file, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ipoib_path_sops = अणु
	.start = ipoib_path_seq_start,
	.next  = ipoib_path_seq_next,
	.stop  = ipoib_path_seq_stop,
	.show  = ipoib_path_seq_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(ipoib_path);

व्योम ipoib_create_debug_files(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	अक्षर name[IFNAMSIZ + माप("_path")];

	snम_लिखो(name, माप(name), "%s_mcg", dev->name);
	priv->mcg_dentry = debugfs_create_file(name, S_IFREG | S_IRUGO,
					       ipoib_root, dev, &ipoib_mcg_fops);

	snम_लिखो(name, माप(name), "%s_path", dev->name);
	priv->path_dentry = debugfs_create_file(name, S_IFREG | S_IRUGO,
						ipoib_root, dev, &ipoib_path_fops);
पूर्ण

व्योम ipoib_delete_debug_files(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	debugfs_हटाओ(priv->mcg_dentry);
	debugfs_हटाओ(priv->path_dentry);
	priv->mcg_dentry = priv->path_dentry = शून्य;
पूर्ण

व्योम ipoib_रेजिस्टर_debugfs(व्योम)
अणु
	ipoib_root = debugfs_create_dir("ipoib", शून्य);
पूर्ण

व्योम ipoib_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ(ipoib_root);
पूर्ण
