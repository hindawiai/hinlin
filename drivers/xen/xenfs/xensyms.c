<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/xen-ops.h>
#समावेश "xenfs.h"


#घोषणा XEN_KSYM_NAME_LEN 127 /* Hypervisor may have dअगरferent name length */

काष्ठा xensyms अणु
	काष्ठा xen_platक्रमm_op op;
	अक्षर *name;
	uपूर्णांक32_t namelen;
पूर्ण;

/* Grab next output page from the hypervisor */
अटल पूर्णांक xensyms_next_sym(काष्ठा xensyms *xs)
अणु
	पूर्णांक ret;
	काष्ठा xenpf_symdata *symdata = &xs->op.u.symdata;
	uपूर्णांक64_t symnum;

	स_रखो(xs->name, 0, xs->namelen);
	symdata->namelen = xs->namelen;

	symnum = symdata->symnum;

	ret = HYPERVISOR_platक्रमm_op(&xs->op);
	अगर (ret < 0)
		वापस ret;

	/*
	 * If hypervisor's symbol didn't fit पूर्णांकo the buffer then allocate
	 * a larger buffer and try again.
	 */
	अगर (unlikely(symdata->namelen > xs->namelen)) अणु
		kमुक्त(xs->name);

		xs->namelen = symdata->namelen;
		xs->name = kzalloc(xs->namelen, GFP_KERNEL);
		अगर (!xs->name)
			वापस -ENOMEM;

		set_xen_guest_handle(symdata->name, xs->name);
		symdata->symnum--; /* Rewind */

		ret = HYPERVISOR_platक्रमm_op(&xs->op);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (symdata->symnum == symnum)
		/* End of symbols */
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम *xensyms_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा xensyms *xs = (काष्ठा xensyms *)m->निजी;

	xs->op.u.symdata.symnum = *pos;

	अगर (xensyms_next_sym(xs))
		वापस शून्य;

	वापस m->निजी;
पूर्ण

अटल व्योम *xensyms_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	काष्ठा xensyms *xs = (काष्ठा xensyms *)m->निजी;

	xs->op.u.symdata.symnum = ++(*pos);

	अगर (xensyms_next_sym(xs))
		वापस शून्य;

	वापस p;
पूर्ण

अटल पूर्णांक xensyms_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा xensyms *xs = (काष्ठा xensyms *)m->निजी;
	काष्ठा xenpf_symdata *symdata = &xs->op.u.symdata;

	seq_म_लिखो(m, "%016llx %c %s\n", symdata->address,
		   symdata->type, xs->name);

	वापस 0;
पूर्ण

अटल व्योम xensyms_stop(काष्ठा seq_file *m, व्योम *p)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations xensyms_seq_ops = अणु
	.start = xensyms_start,
	.next = xensyms_next,
	.show = xensyms_show,
	.stop = xensyms_stop,
पूर्ण;

अटल पूर्णांक xensyms_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m;
	काष्ठा xensyms *xs;
	पूर्णांक ret;

	ret = seq_खोलो_निजी(file, &xensyms_seq_ops,
			       माप(काष्ठा xensyms));
	अगर (ret)
		वापस ret;

	m = file->निजी_data;
	xs = (काष्ठा xensyms *)m->निजी;

	xs->namelen = XEN_KSYM_NAME_LEN + 1;
	xs->name = kzalloc(xs->namelen, GFP_KERNEL);
	अगर (!xs->name) अणु
		seq_release_निजी(inode, file);
		वापस -ENOMEM;
	पूर्ण
	set_xen_guest_handle(xs->op.u.symdata.name, xs->name);
	xs->op.cmd = XENPF_get_symbol;
	xs->op.u.symdata.namelen = xs->namelen;

	वापस 0;
पूर्ण

अटल पूर्णांक xensyms_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा xensyms *xs = (काष्ठा xensyms *)m->निजी;

	kमुक्त(xs->name);
	वापस seq_release_निजी(inode, file);
पूर्ण

स्थिर काष्ठा file_operations xensyms_ops = अणु
	.खोलो = xensyms_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = xensyms_release
पूर्ण;
