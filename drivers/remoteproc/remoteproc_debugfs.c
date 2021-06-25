<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote Processor Framework
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Mark Grosen <mgrosen@ti.com>
 * Brian Swetland <swetland@google.com>
 * Fernanकरो Guzman Lugo <fernanकरो.lugo@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Robert Tivy <rtivy@ti.com>
 * Armanकरो Uribe De Leon <x0095078@ti.com>
 */

#घोषणा pr_fmt(fmt)    "%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>

#समावेश "remoteproc_internal.h"

/* remoteproc debugfs parent dir */
अटल काष्ठा dentry *rproc_dbg;

/*
 * A coredump-configuration-to-string lookup table, क्रम exposing a
 * human पढ़ोable configuration via debugfs. Always keep in sync with
 * क्रमागत rproc_coredump_mechanism
 */
अटल स्थिर अक्षर * स्थिर rproc_coredump_str[] = अणु
	[RPROC_COREDUMP_DISABLED]	= "disabled",
	[RPROC_COREDUMP_ENABLED]	= "enabled",
	[RPROC_COREDUMP_INLINE]		= "inline",
पूर्ण;

/* Expose the current coredump configuration via debugfs */
अटल sमाप_प्रकार rproc_coredump_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rproc *rproc = filp->निजी_data;
	अक्षर buf[20];
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf), "%s\n",
			rproc_coredump_str[rproc->dump_conf]);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

/*
 * By writing to the 'coredump' debugfs entry, we control the behavior of the
 * coredump mechanism dynamically. The शेष value of this entry is "disabled".
 *
 * The 'coredump' debugfs entry supports these commands:
 *
 * disabled:	By शेष coredump collection is disabled. Recovery will
 *		proceed without collecting any dump.
 *
 * enabled:	When the remoteproc crashes the entire coredump will be copied
 *		to a separate buffer and exposed to userspace.
 *
 * अंतरभूत:	The coredump will not be copied to a separate buffer and the
 *		recovery process will have to रुको until data is पढ़ो by
 *		userspace. But this aव्योम usage of extra memory.
 */
अटल sमाप_प्रकार rproc_coredump_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				    loff_t *ppos)
अणु
	काष्ठा rproc *rproc = filp->निजी_data;
	पूर्णांक ret, err = 0;
	अक्षर buf[20];

	अगर (count > माप(buf))
		वापस -EINVAL;

	ret = copy_from_user(buf, user_buf, count);
	अगर (ret)
		वापस -EFAULT;

	/* हटाओ end of line */
	अगर (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	अगर (rproc->state == RPROC_CRASHED) अणु
		dev_err(&rproc->dev, "can't change coredump configuration\n");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!म_भेदन(buf, "disabled", count)) अणु
		rproc->dump_conf = RPROC_COREDUMP_DISABLED;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "enabled", count)) अणु
		rproc->dump_conf = RPROC_COREDUMP_ENABLED;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "inline", count)) अणु
		rproc->dump_conf = RPROC_COREDUMP_INLINE;
	पूर्ण अन्यथा अणु
		dev_err(&rproc->dev, "Invalid coredump configuration\n");
		err = -EINVAL;
	पूर्ण
out:
	वापस err ? err : count;
पूर्ण

अटल स्थिर काष्ठा file_operations rproc_coredump_fops = अणु
	.पढ़ो = rproc_coredump_पढ़ो,
	.ग_लिखो = rproc_coredump_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
पूर्ण;

/*
 * Some remote processors may support dumping trace logs पूर्णांकo a shared
 * memory buffer. We expose this trace buffer using debugfs, so users
 * can easily tell what's going on remotely.
 *
 * We will most probably improve the rproc tracing facilities later on,
 * but this kind of lightweight and simple mechanism is always good to have,
 * as it provides very early tracing with little to no dependencies at all.
 */
अटल sमाप_प्रकार rproc_trace_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rproc_debug_trace *data = filp->निजी_data;
	काष्ठा rproc_mem_entry *trace = &data->trace_mem;
	व्योम *va;
	अक्षर buf[100];
	पूर्णांक len;

	va = rproc_da_to_va(data->rproc, trace->da, trace->len, शून्य);

	अगर (!va) अणु
		len = scnम_लिखो(buf, माप(buf), "Trace %s not available\n",
				trace->name);
		va = buf;
	पूर्ण अन्यथा अणु
		len = strnlen(va, trace->len);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, va, len);
पूर्ण

अटल स्थिर काष्ठा file_operations trace_rproc_ops = अणु
	.पढ़ो = rproc_trace_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek	= generic_file_llseek,
पूर्ण;

/* expose the name of the remote processor via debugfs */
अटल sमाप_प्रकार rproc_name_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rproc *rproc = filp->निजी_data;
	/* need room क्रम the name, a newline and a terminating null */
	अक्षर buf[100];
	पूर्णांक i;

	i = scnम_लिखो(buf, माप(buf), "%.98s\n", rproc->name);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, i);
पूर्ण

अटल स्थिर काष्ठा file_operations rproc_name_ops = अणु
	.पढ़ो = rproc_name_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek	= generic_file_llseek,
पूर्ण;

/* expose recovery flag via debugfs */
अटल sमाप_प्रकार rproc_recovery_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rproc *rproc = filp->निजी_data;
	अक्षर *buf = rproc->recovery_disabled ? "disabled\n" : "enabled\n";

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, म_माप(buf));
पूर्ण

/*
 * By writing to the 'recovery' debugfs entry, we control the behavior of the
 * recovery mechanism dynamically. The शेष value of this entry is "enabled".
 *
 * The 'recovery' debugfs entry supports these commands:
 *
 * enabled:	When enabled, the remote processor will be स्वतःmatically
 *		recovered whenever it crashes. Moreover, अगर the remote
 *		processor crashes जबतक recovery is disabled, it will
 *		be स्वतःmatically recovered too as soon as recovery is enabled.
 *
 * disabled:	When disabled, a remote processor will reमुख्य in a crashed
 *		state अगर it crashes. This is useful क्रम debugging purposes;
 *		without it, debugging a crash is substantially harder.
 *
 * recover:	This function will trigger an immediate recovery अगर the
 *		remote processor is in a crashed state, without changing
 *		or checking the recovery state (enabled/disabled).
 *		This is useful during debugging sessions, when one expects
 *		additional crashes to happen after enabling recovery. In this
 *		हाल, enabling recovery will make it hard to debug subsequent
 *		crashes, so it's recommended to keep recovery disabled, and
 *		instead use the "recover" command as needed.
 */
अटल sमाप_प्रकार
rproc_recovery_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *user_buf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rproc *rproc = filp->निजी_data;
	अक्षर buf[10];
	पूर्णांक ret;

	अगर (count < 1 || count > माप(buf))
		वापस -EINVAL;

	ret = copy_from_user(buf, user_buf, count);
	अगर (ret)
		वापस -EFAULT;

	/* हटाओ end of line */
	अगर (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	अगर (!म_भेदन(buf, "enabled", count)) अणु
		/* change the flag and begin the recovery process अगर needed */
		rproc->recovery_disabled = false;
		rproc_trigger_recovery(rproc);
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "disabled", count)) अणु
		rproc->recovery_disabled = true;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "recover", count)) अणु
		/* begin the recovery process without changing the flag */
		rproc_trigger_recovery(rproc);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations rproc_recovery_ops = अणु
	.पढ़ो = rproc_recovery_पढ़ो,
	.ग_लिखो = rproc_recovery_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
पूर्ण;

/* expose the crash trigger via debugfs */
अटल sमाप_प्रकार
rproc_crash_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *user_buf,
		  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rproc *rproc = filp->निजी_data;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक_from_user(user_buf, count, 0, &type);
	अगर (ret < 0)
		वापस ret;

	rproc_report_crash(rproc, type);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations rproc_crash_ops = अणु
	.ग_लिखो = rproc_crash_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
पूर्ण;

/* Expose resource table content via debugfs */
अटल पूर्णांक rproc_rsc_table_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	अटल स्थिर अक्षर * स्थिर types[] = अणु"carveout", "devmem", "trace", "vdev"पूर्ण;
	काष्ठा rproc *rproc = seq->निजी;
	काष्ठा resource_table *table = rproc->table_ptr;
	काष्ठा fw_rsc_carveout *c;
	काष्ठा fw_rsc_devmem *d;
	काष्ठा fw_rsc_trace *t;
	काष्ठा fw_rsc_vdev *v;
	पूर्णांक i, j;

	अगर (!table) अणु
		seq_माला_दो(seq, "No resource table found\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < table->num; i++) अणु
		पूर्णांक offset = table->offset[i];
		काष्ठा fw_rsc_hdr *hdr = (व्योम *)table + offset;
		व्योम *rsc = (व्योम *)hdr + माप(*hdr);

		चयन (hdr->type) अणु
		हाल RSC_CARVEOUT:
			c = rsc;
			seq_म_लिखो(seq, "Entry %d is of type %s\n", i, types[hdr->type]);
			seq_म_लिखो(seq, "  Device Address 0x%x\n", c->da);
			seq_म_लिखो(seq, "  Physical Address 0x%x\n", c->pa);
			seq_म_लिखो(seq, "  Length 0x%x Bytes\n", c->len);
			seq_म_लिखो(seq, "  Flags 0x%x\n", c->flags);
			seq_म_लिखो(seq, "  Reserved (should be zero) [%d]\n", c->reserved);
			seq_म_लिखो(seq, "  Name %s\n\n", c->name);
			अवरोध;
		हाल RSC_DEVMEM:
			d = rsc;
			seq_म_लिखो(seq, "Entry %d is of type %s\n", i, types[hdr->type]);
			seq_म_लिखो(seq, "  Device Address 0x%x\n", d->da);
			seq_म_लिखो(seq, "  Physical Address 0x%x\n", d->pa);
			seq_म_लिखो(seq, "  Length 0x%x Bytes\n", d->len);
			seq_म_लिखो(seq, "  Flags 0x%x\n", d->flags);
			seq_म_लिखो(seq, "  Reserved (should be zero) [%d]\n", d->reserved);
			seq_म_लिखो(seq, "  Name %s\n\n", d->name);
			अवरोध;
		हाल RSC_TRACE:
			t = rsc;
			seq_म_लिखो(seq, "Entry %d is of type %s\n", i, types[hdr->type]);
			seq_म_लिखो(seq, "  Device Address 0x%x\n", t->da);
			seq_म_लिखो(seq, "  Length 0x%x Bytes\n", t->len);
			seq_म_लिखो(seq, "  Reserved (should be zero) [%d]\n", t->reserved);
			seq_म_लिखो(seq, "  Name %s\n\n", t->name);
			अवरोध;
		हाल RSC_VDEV:
			v = rsc;
			seq_म_लिखो(seq, "Entry %d is of type %s\n", i, types[hdr->type]);

			seq_म_लिखो(seq, "  ID %d\n", v->id);
			seq_म_लिखो(seq, "  Notify ID %d\n", v->notअगरyid);
			seq_म_लिखो(seq, "  Device features 0x%x\n", v->dfeatures);
			seq_म_लिखो(seq, "  Guest features 0x%x\n", v->gfeatures);
			seq_म_लिखो(seq, "  Config length 0x%x\n", v->config_len);
			seq_म_लिखो(seq, "  Status 0x%x\n", v->status);
			seq_म_लिखो(seq, "  Number of vrings %d\n", v->num_of_vrings);
			seq_म_लिखो(seq, "  Reserved (should be zero) [%d][%d]\n\n",
				   v->reserved[0], v->reserved[1]);

			क्रम (j = 0; j < v->num_of_vrings; j++) अणु
				seq_म_लिखो(seq, "  Vring %d\n", j);
				seq_म_लिखो(seq, "    Device Address 0x%x\n", v->vring[j].da);
				seq_म_लिखो(seq, "    Alignment %d\n", v->vring[j].align);
				seq_म_लिखो(seq, "    Number of buffers %d\n", v->vring[j].num);
				seq_म_लिखो(seq, "    Notify ID %d\n", v->vring[j].notअगरyid);
				seq_म_लिखो(seq, "    Physical Address 0x%x\n\n",
					   v->vring[j].pa);
			पूर्ण
			अवरोध;
		शेष:
			seq_म_लिखो(seq, "Unknown resource type found: %d [hdr: %pK]\n",
				   hdr->type, hdr);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rproc_rsc_table);

/* Expose carveout content via debugfs */
अटल पूर्णांक rproc_carveouts_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा rproc *rproc = seq->निजी;
	काष्ठा rproc_mem_entry *carveout;

	list_क्रम_each_entry(carveout, &rproc->carveouts, node) अणु
		seq_माला_दो(seq, "Carveout memory entry:\n");
		seq_म_लिखो(seq, "\tName: %s\n", carveout->name);
		seq_म_लिखो(seq, "\tVirtual address: %pK\n", carveout->va);
		seq_म_लिखो(seq, "\tDMA address: %pad\n", &carveout->dma);
		seq_म_लिखो(seq, "\tDevice address: 0x%x\n", carveout->da);
		seq_म_लिखो(seq, "\tLength: 0x%zx Bytes\n\n", carveout->len);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rproc_carveouts);

व्योम rproc_हटाओ_trace_file(काष्ठा dentry *tfile)
अणु
	debugfs_हटाओ(tfile);
पूर्ण

काष्ठा dentry *rproc_create_trace_file(स्थिर अक्षर *name, काष्ठा rproc *rproc,
				       काष्ठा rproc_debug_trace *trace)
अणु
	काष्ठा dentry *tfile;

	tfile = debugfs_create_file(name, 0400, rproc->dbg_dir, trace,
				    &trace_rproc_ops);
	अगर (!tfile) अणु
		dev_err(&rproc->dev, "failed to create debugfs trace entry\n");
		वापस शून्य;
	पूर्ण

	वापस tfile;
पूर्ण

व्योम rproc_delete_debug_dir(काष्ठा rproc *rproc)
अणु
	debugfs_हटाओ_recursive(rproc->dbg_dir);
पूर्ण

व्योम rproc_create_debug_dir(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;

	अगर (!rproc_dbg)
		वापस;

	rproc->dbg_dir = debugfs_create_dir(dev_name(dev), rproc_dbg);
	अगर (!rproc->dbg_dir)
		वापस;

	debugfs_create_file("name", 0400, rproc->dbg_dir,
			    rproc, &rproc_name_ops);
	debugfs_create_file("recovery", 0600, rproc->dbg_dir,
			    rproc, &rproc_recovery_ops);
	debugfs_create_file("crash", 0200, rproc->dbg_dir,
			    rproc, &rproc_crash_ops);
	debugfs_create_file("resource_table", 0400, rproc->dbg_dir,
			    rproc, &rproc_rsc_table_fops);
	debugfs_create_file("carveout_memories", 0400, rproc->dbg_dir,
			    rproc, &rproc_carveouts_fops);
	debugfs_create_file("coredump", 0600, rproc->dbg_dir,
			    rproc, &rproc_coredump_fops);
पूर्ण

व्योम __init rproc_init_debugfs(व्योम)
अणु
	अगर (debugfs_initialized()) अणु
		rproc_dbg = debugfs_create_dir(KBUILD_MODNAME, शून्य);
		अगर (!rproc_dbg)
			pr_err("can't create debugfs dir\n");
	पूर्ण
पूर्ण

व्योम __निकास rproc_निकास_debugfs(व्योम)
अणु
	debugfs_हटाओ(rproc_dbg);
पूर्ण
