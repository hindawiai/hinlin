<शैली गुरु>
/*
 * Kernel CAPI 2.0 Module - /proc/capi handling
 *
 * Copyright 1999 by Carsten Paeth <calle@calle.de>
 * Copyright 2002 by Kai Germaschewski <kai@germaschewski.name>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */


#समावेश "kcapi.h"
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>

अटल अक्षर *state2str(अचिन्हित लघु state)
अणु
	चयन (state) अणु
	हाल CAPI_CTR_DETECTED:	वापस "detected";
	हाल CAPI_CTR_LOADING:	वापस "loading";
	हाल CAPI_CTR_RUNNING:	वापस "running";
	शेष:	        वापस "???";
	पूर्ण
पूर्ण

// /proc/capi
// ===========================================================================

// /proc/capi/controller:
//      cnr driver cardstate name driverinfo
// /proc/capi/contrstats:
//      cnr nrecvctlpkt nrecvdatapkt nsentctlpkt nsentdatapkt
// ---------------------------------------------------------------------------

अटल व्योम *controller_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(capi_controller_lock)
अणु
	mutex_lock(&capi_controller_lock);

	अगर (*pos < CAPI_MAXCONTR)
		वापस &capi_controller[*pos];

	वापस शून्य;
पूर्ण

अटल व्योम *controller_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	अगर (*pos < CAPI_MAXCONTR)
		वापस &capi_controller[*pos];

	वापस शून्य;
पूर्ण

अटल व्योम controller_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(capi_controller_lock)
अणु
	mutex_unlock(&capi_controller_lock);
पूर्ण

अटल पूर्णांक controller_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा capi_ctr *ctr = *(काष्ठा capi_ctr **) v;

	अगर (!ctr)
		वापस 0;

	seq_म_लिखो(seq, "%d %-10s %-8s %-16s %s\n",
		   ctr->cnr, ctr->driver_name,
		   state2str(ctr->state),
		   ctr->name,
		   ctr->procinfo ?  ctr->procinfo(ctr) : "");

	वापस 0;
पूर्ण

अटल पूर्णांक contrstats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा capi_ctr *ctr = *(काष्ठा capi_ctr **) v;

	अगर (!ctr)
		वापस 0;

	seq_म_लिखो(seq, "%d %lu %lu %lu %lu\n",
		   ctr->cnr,
		   ctr->nrecvctlpkt,
		   ctr->nrecvdatapkt,
		   ctr->nsentctlpkt,
		   ctr->nsentdatapkt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations seq_controller_ops = अणु
	.start	= controller_start,
	.next	= controller_next,
	.stop	= controller_stop,
	.show	= controller_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations seq_contrstats_ops = अणु
	.start	= controller_start,
	.next	= controller_next,
	.stop	= controller_stop,
	.show	= contrstats_show,
पूर्ण;

// /proc/capi/applications:
//      applid l3cnt dblkcnt dblklen #ncci recvqueuelen
// /proc/capi/applstats:
//      applid nrecvctlpkt nrecvdatapkt nsentctlpkt nsentdatapkt
// ---------------------------------------------------------------------------

अटल व्योम *applications_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(capi_controller_lock)
अणु
	mutex_lock(&capi_controller_lock);

	अगर (*pos < CAPI_MAXAPPL)
		वापस &capi_applications[*pos];

	वापस शून्य;
पूर्ण

अटल व्योम *
applications_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	अगर (*pos < CAPI_MAXAPPL)
		वापस &capi_applications[*pos];

	वापस शून्य;
पूर्ण

अटल व्योम applications_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(capi_controller_lock)
अणु
	mutex_unlock(&capi_controller_lock);
पूर्ण

अटल पूर्णांक
applications_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा capi20_appl *ap = *(काष्ठा capi20_appl **) v;

	अगर (!ap)
		वापस 0;

	seq_म_लिखो(seq, "%u %d %d %d\n",
		   ap->applid,
		   ap->rparam.level3cnt,
		   ap->rparam.datablkcnt,
		   ap->rparam.datablklen);

	वापस 0;
पूर्ण

अटल पूर्णांक
applstats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा capi20_appl *ap = *(काष्ठा capi20_appl **) v;

	अगर (!ap)
		वापस 0;

	seq_म_लिखो(seq, "%u %lu %lu %lu %lu\n",
		   ap->applid,
		   ap->nrecvctlpkt,
		   ap->nrecvdatapkt,
		   ap->nsentctlpkt,
		   ap->nsentdatapkt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations seq_applications_ops = अणु
	.start	= applications_start,
	.next	= applications_next,
	.stop	= applications_stop,
	.show	= applications_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations seq_applstats_ops = अणु
	.start	= applications_start,
	.next	= applications_next,
	.stop	= applications_stop,
	.show	= applstats_show,
पूर्ण;

// ---------------------------------------------------------------------------

/* /proc/capi/drivers is always empty */
अटल sमाप_प्रकार empty_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार size, loff_t *off)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops empty_proc_ops = अणु
	.proc_पढ़ो	= empty_पढ़ो,
	.proc_lseek	= शेष_llseek,
पूर्ण;

// ---------------------------------------------------------------------------

व्योम __init
kcapi_proc_init(व्योम)
अणु
	proc_सूची_गढ़ो("capi",             शून्य);
	proc_सूची_गढ़ो("capi/controllers", शून्य);
	proc_create_seq("capi/controller",   0, शून्य, &seq_controller_ops);
	proc_create_seq("capi/contrstats",   0, शून्य, &seq_contrstats_ops);
	proc_create_seq("capi/applications", 0, शून्य, &seq_applications_ops);
	proc_create_seq("capi/applstats",    0, शून्य, &seq_applstats_ops);
	proc_create("capi/driver",           0, शून्य, &empty_proc_ops);
पूर्ण

व्योम
kcapi_proc_निकास(व्योम)
अणु
	हटाओ_proc_entry("capi/driver",       शून्य);
	हटाओ_proc_entry("capi/controller",   शून्य);
	हटाओ_proc_entry("capi/contrstats",   शून्य);
	हटाओ_proc_entry("capi/applications", शून्य);
	हटाओ_proc_entry("capi/applstats",    शून्य);
	हटाओ_proc_entry("capi/controllers",  शून्य);
	हटाओ_proc_entry("capi",              शून्य);
पूर्ण
