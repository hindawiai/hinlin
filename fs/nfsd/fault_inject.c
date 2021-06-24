<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011 Bryan Schumaker <bjschuma@netapp.com>
 *
 * Uses debugfs to create fault injection poपूर्णांकs क्रम client testing
 */

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>

#समावेश "state.h"
#समावेश "netns.h"

काष्ठा nfsd_fault_inject_op अणु
	अक्षर *file;
	u64 (*get)(व्योम);
	u64 (*set_val)(u64);
	u64 (*set_clnt)(काष्ठा sockaddr_storage *, माप_प्रकार);
पूर्ण;

अटल काष्ठा dentry *debug_dir;

अटल sमाप_प्रकार fault_inject_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार len, loff_t *ppos)
अणु
	अटल u64 val;
	अक्षर पढ़ो_buf[25];
	माप_प्रकार size;
	loff_t pos = *ppos;
	काष्ठा nfsd_fault_inject_op *op = file_inode(file)->i_निजी;

	अगर (!pos)
		val = op->get();
	size = scnम_लिखो(पढ़ो_buf, माप(पढ़ो_buf), "%llu\n", val);

	वापस simple_पढ़ो_from_buffer(buf, len, ppos, पढ़ो_buf, size);
पूर्ण

अटल sमाप_प्रकार fault_inject_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार len, loff_t *ppos)
अणु
	अक्षर ग_लिखो_buf[INET6_ADDRSTRLEN];
	माप_प्रकार size = min(माप(ग_लिखो_buf) - 1, len);
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा sockaddr_storage sa;
	काष्ठा nfsd_fault_inject_op *op = file_inode(file)->i_निजी;
	u64 val;
	अक्षर *nl;

	अगर (copy_from_user(ग_लिखो_buf, buf, size))
		वापस -EFAULT;
	ग_लिखो_buf[size] = '\0';

	/* Deal with any embedded newlines in the string */
	nl = म_अक्षर(ग_लिखो_buf, '\n');
	अगर (nl) अणु
		size = nl - ग_लिखो_buf;
		*nl = '\0';
	पूर्ण

	size = rpc_pton(net, ग_लिखो_buf, size, (काष्ठा sockaddr *)&sa, माप(sa));
	अगर (size > 0) अणु
		val = op->set_clnt(&sa, size);
		अगर (val)
			pr_info("NFSD [%s]: Client %s had %llu state object(s)\n",
				op->file, ग_लिखो_buf, val);
	पूर्ण अन्यथा अणु
		val = simple_म_से_दीर्घl(ग_लिखो_buf, शून्य, 0);
		अगर (val == 0)
			pr_info("NFSD Fault Injection: %s (all)", op->file);
		अन्यथा
			pr_info("NFSD Fault Injection: %s (n = %llu)",
				op->file, val);
		val = op->set_val(val);
		pr_info("NFSD: %s: found %llu", op->file, val);
	पूर्ण
	वापस len; /* on success, claim we got the whole input */
पूर्ण

अटल स्थिर काष्ठा file_operations fops_nfsd = अणु
	.owner   = THIS_MODULE,
	.पढ़ो    = fault_inject_पढ़ो,
	.ग_लिखो   = fault_inject_ग_लिखो,
पूर्ण;

व्योम nfsd_fault_inject_cleanup(व्योम)
अणु
	debugfs_हटाओ_recursive(debug_dir);
पूर्ण

अटल काष्ठा nfsd_fault_inject_op inject_ops[] = अणु
	अणु
		.file     = "forget_clients",
		.get	  = nfsd_inject_prपूर्णांक_clients,
		.set_val  = nfsd_inject_क्रमget_clients,
		.set_clnt = nfsd_inject_क्रमget_client,
	पूर्ण,
	अणु
		.file     = "forget_locks",
		.get	  = nfsd_inject_prपूर्णांक_locks,
		.set_val  = nfsd_inject_क्रमget_locks,
		.set_clnt = nfsd_inject_क्रमget_client_locks,
	पूर्ण,
	अणु
		.file     = "forget_openowners",
		.get	  = nfsd_inject_prपूर्णांक_खोलोowners,
		.set_val  = nfsd_inject_क्रमget_खोलोowners,
		.set_clnt = nfsd_inject_क्रमget_client_खोलोowners,
	पूर्ण,
	अणु
		.file     = "forget_delegations",
		.get	  = nfsd_inject_prपूर्णांक_delegations,
		.set_val  = nfsd_inject_क्रमget_delegations,
		.set_clnt = nfsd_inject_क्रमget_client_delegations,
	पूर्ण,
	अणु
		.file     = "recall_delegations",
		.get	  = nfsd_inject_prपूर्णांक_delegations,
		.set_val  = nfsd_inject_recall_delegations,
		.set_clnt = nfsd_inject_recall_client_delegations,
	पूर्ण,
पूर्ण;

व्योम nfsd_fault_inject_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा nfsd_fault_inject_op *op;
	umode_t mode = S_IFREG | S_IRUSR | S_IWUSR;

	debug_dir = debugfs_create_dir("nfsd", शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(inject_ops); i++) अणु
		op = &inject_ops[i];
		debugfs_create_file(op->file, mode, debug_dir, op, &fops_nfsd);
	पूर्ण
पूर्ण
