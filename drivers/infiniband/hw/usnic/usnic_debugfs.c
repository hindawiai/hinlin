<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>

#समावेश "usnic.h"
#समावेश "usnic_log.h"
#समावेश "usnic_debugfs.h"
#समावेश "usnic_ib_qp_grp.h"
#समावेश "usnic_transport.h"

अटल काष्ठा dentry *debugfs_root;
अटल काष्ठा dentry *flows_dentry;

अटल sमाप_प्रकार usnic_debugfs_buildinfo_पढ़ो(काष्ठा file *f, अक्षर __user *data,
						माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[500];
	पूर्णांक res;

	अगर (*ppos > 0)
		वापस 0;

	res = scnम_लिखो(buf, माप(buf),
			"version:       %s\n"
			"build date:    %s\n",
			DRV_VERSION, DRV_RELDATE);

	वापस simple_पढ़ो_from_buffer(data, count, ppos, buf, res);
पूर्ण

अटल स्थिर काष्ठा file_operations usnic_debugfs_buildinfo_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = usnic_debugfs_buildinfo_पढ़ो
पूर्ण;

अटल sमाप_प्रकार flowinfo_पढ़ो(काष्ठा file *f, अक्षर __user *data,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा usnic_ib_qp_grp_flow *qp_flow;
	पूर्णांक n;
	पूर्णांक left;
	अक्षर *ptr;
	अक्षर buf[512];

	qp_flow = f->निजी_data;
	ptr = buf;
	left = count;

	अगर (*ppos > 0)
		वापस 0;

	spin_lock(&qp_flow->qp_grp->lock);
	n = scnम_लिखो(ptr, left,
			"QP Grp ID: %d Transport: %s ",
			qp_flow->qp_grp->grp_id,
			usnic_transport_to_str(qp_flow->trans_type));
	UPDATE_PTR_LEFT(n, ptr, left);
	अगर (qp_flow->trans_type == USNIC_TRANSPORT_ROCE_CUSTOM) अणु
		n = scnम_लिखो(ptr, left, "Port_Num:%hu\n",
					qp_flow->usnic_roce.port_num);
		UPDATE_PTR_LEFT(n, ptr, left);
	पूर्ण अन्यथा अगर (qp_flow->trans_type == USNIC_TRANSPORT_IPV4_UDP) अणु
		n = usnic_transport_sock_to_str(ptr, left,
				qp_flow->udp.sock);
		UPDATE_PTR_LEFT(n, ptr, left);
		n = scnम_लिखो(ptr, left, "\n");
		UPDATE_PTR_LEFT(n, ptr, left);
	पूर्ण
	spin_unlock(&qp_flow->qp_grp->lock);

	वापस simple_पढ़ो_from_buffer(data, count, ppos, buf, ptr - buf);
पूर्ण

अटल स्थिर काष्ठा file_operations flowinfo_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = flowinfo_पढ़ो,
पूर्ण;

व्योम usnic_debugfs_init(व्योम)
अणु
	debugfs_root = debugfs_create_dir(DRV_NAME, शून्य);

	flows_dentry = debugfs_create_dir("flows", debugfs_root);

	debugfs_create_file("build-info", S_IRUGO, debugfs_root,
				शून्य, &usnic_debugfs_buildinfo_ops);
पूर्ण

व्योम usnic_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_root);
	debugfs_root = शून्य;
पूर्ण

व्योम usnic_debugfs_flow_add(काष्ठा usnic_ib_qp_grp_flow *qp_flow)
अणु
	scnम_लिखो(qp_flow->dentry_name, माप(qp_flow->dentry_name),
			"%u", qp_flow->flow->flow_id);
	qp_flow->dbgfs_dentry = debugfs_create_file(qp_flow->dentry_name,
							S_IRUGO,
							flows_dentry,
							qp_flow,
							&flowinfo_ops);
पूर्ण

व्योम usnic_debugfs_flow_हटाओ(काष्ठा usnic_ib_qp_grp_flow *qp_flow)
अणु
	debugfs_हटाओ(qp_flow->dbgfs_dentry);
पूर्ण
