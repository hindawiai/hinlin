<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 *
 * This file is part of the SCTP kernel implementation
 *
 * Support क्रम memory object debugging.  This allows one to monitor the
 * object allocations/deallocations क्रम types instrumented क्रम this
 * via the proc fs.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Jon Grimm             <jgrimm@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <net/sctp/sctp.h>

/*
 * Global counters to count raw object allocation counts.
 * To add new counters, choose a unique suffix क्रम the variable
 * name as the helper macros key off this suffix to make
 * lअगरe easier क्रम the programmer.
 */

SCTP_DBG_OBJCNT(sock);
SCTP_DBG_OBJCNT(ep);
SCTP_DBG_OBJCNT(transport);
SCTP_DBG_OBJCNT(assoc);
SCTP_DBG_OBJCNT(bind_addr);
SCTP_DBG_OBJCNT(bind_bucket);
SCTP_DBG_OBJCNT(chunk);
SCTP_DBG_OBJCNT(addr);
SCTP_DBG_OBJCNT(datamsg);
SCTP_DBG_OBJCNT(keys);

/* An array to make it easy to pretty prपूर्णांक the debug inक्रमmation
 * to the proc fs.
 */
अटल काष्ठा sctp_dbg_objcnt_entry sctp_dbg_objcnt[] = अणु
	SCTP_DBG_OBJCNT_ENTRY(sock),
	SCTP_DBG_OBJCNT_ENTRY(ep),
	SCTP_DBG_OBJCNT_ENTRY(assoc),
	SCTP_DBG_OBJCNT_ENTRY(transport),
	SCTP_DBG_OBJCNT_ENTRY(chunk),
	SCTP_DBG_OBJCNT_ENTRY(bind_addr),
	SCTP_DBG_OBJCNT_ENTRY(bind_bucket),
	SCTP_DBG_OBJCNT_ENTRY(addr),
	SCTP_DBG_OBJCNT_ENTRY(datamsg),
	SCTP_DBG_OBJCNT_ENTRY(keys),
पूर्ण;

/* Callback from procfs to पढ़ो out objcount inक्रमmation.
 * Walk through the entries in the sctp_dbg_objcnt array, dumping
 * the raw object counts क्रम each monitored type.
 */
अटल पूर्णांक sctp_objcnt_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	i = (पूर्णांक)*(loff_t *)v;
	seq_setwidth(seq, 127);
	seq_म_लिखो(seq, "%s: %d", sctp_dbg_objcnt[i].label,
				atomic_पढ़ो(sctp_dbg_objcnt[i].counter));
	seq_pad(seq, '\n');
	वापस 0;
पूर्ण

अटल व्योम *sctp_objcnt_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस (*pos >= ARRAY_SIZE(sctp_dbg_objcnt)) ? शून्य : (व्योम *)pos;
पूर्ण

अटल व्योम sctp_objcnt_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल व्योम *sctp_objcnt_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस (*pos >= ARRAY_SIZE(sctp_dbg_objcnt)) ? शून्य : (व्योम *)pos;
पूर्ण

अटल स्थिर काष्ठा seq_operations sctp_objcnt_seq_ops = अणु
	.start = sctp_objcnt_seq_start,
	.next  = sctp_objcnt_seq_next,
	.stop  = sctp_objcnt_seq_stop,
	.show  = sctp_objcnt_seq_show,
पूर्ण;

/* Initialize the objcount in the proc fileप्रणाली.  */
व्योम sctp_dbg_objcnt_init(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *ent;

	ent = proc_create_seq("sctp_dbg_objcnt", 0,
			  net->sctp.proc_net_sctp, &sctp_objcnt_seq_ops);
	अगर (!ent)
		pr_warn("sctp_dbg_objcnt: Unable to create /proc entry.\n");
पूर्ण
