<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016-17 IBM Corp.
 */

#घोषणा pr_fmt(fmt) "vas: " fmt

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश "vas.h"

अटल काष्ठा dentry *vas_debugfs;

अटल अक्षर *cop_to_str(पूर्णांक cop)
अणु
	चयन (cop) अणु
	हाल VAS_COP_TYPE_FAULT:	वापस "Fault";
	हाल VAS_COP_TYPE_842:		वापस "NX-842 Normal Priority";
	हाल VAS_COP_TYPE_842_HIPRI:	वापस "NX-842 High Priority";
	हाल VAS_COP_TYPE_GZIP:		वापस "NX-GZIP Normal Priority";
	हाल VAS_COP_TYPE_GZIP_HIPRI:	वापस "NX-GZIP High Priority";
	हाल VAS_COP_TYPE_FTW:		वापस "Fast Thread-wakeup";
	शेष:			वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक info_show(काष्ठा seq_file *s, व्योम *निजी)
अणु
	काष्ठा vas_winकरोw *winकरोw = s->निजी;

	mutex_lock(&vas_mutex);

	/* ensure winकरोw is not unmapped */
	अगर (!winकरोw->hvwc_map)
		जाओ unlock;

	seq_म_लिखो(s, "Type: %s, %s\n", cop_to_str(winकरोw->cop),
					winकरोw->tx_win ? "Send" : "Receive");
	seq_म_लिखो(s, "Pid : %d\n", vas_winकरोw_pid(winकरोw));

unlock:
	mutex_unlock(&vas_mutex);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(info);

अटल अंतरभूत व्योम prपूर्णांक_reg(काष्ठा seq_file *s, काष्ठा vas_winकरोw *win,
			अक्षर *name, u32 reg)
अणु
	seq_म_लिखो(s, "0x%016llx %s\n", पढ़ो_hvwc_reg(win, name, reg), name);
पूर्ण

अटल पूर्णांक hvwc_show(काष्ठा seq_file *s, व्योम *निजी)
अणु
	काष्ठा vas_winकरोw *winकरोw = s->निजी;

	mutex_lock(&vas_mutex);

	/* ensure winकरोw is not unmapped */
	अगर (!winकरोw->hvwc_map)
		जाओ unlock;

	prपूर्णांक_reg(s, winकरोw, VREG(LPID));
	prपूर्णांक_reg(s, winकरोw, VREG(PID));
	prपूर्णांक_reg(s, winकरोw, VREG(XLATE_MSR));
	prपूर्णांक_reg(s, winकरोw, VREG(XLATE_LPCR));
	prपूर्णांक_reg(s, winकरोw, VREG(XLATE_CTL));
	prपूर्णांक_reg(s, winकरोw, VREG(AMR));
	prपूर्णांक_reg(s, winकरोw, VREG(SEIDR));
	prपूर्णांक_reg(s, winकरोw, VREG(FAULT_TX_WIN));
	prपूर्णांक_reg(s, winकरोw, VREG(OSU_INTR_SRC_RA));
	prपूर्णांक_reg(s, winकरोw, VREG(HV_INTR_SRC_RA));
	prपूर्णांक_reg(s, winकरोw, VREG(PSWID));
	prपूर्णांक_reg(s, winकरोw, VREG(LFIFO_BAR));
	prपूर्णांक_reg(s, winकरोw, VREG(LDATA_STAMP_CTL));
	prपूर्णांक_reg(s, winकरोw, VREG(LDMA_CACHE_CTL));
	prपूर्णांक_reg(s, winकरोw, VREG(LRFIFO_PUSH));
	prपूर्णांक_reg(s, winकरोw, VREG(CURR_MSG_COUNT));
	prपूर्णांक_reg(s, winकरोw, VREG(LNOTIFY_AFTER_COUNT));
	prपूर्णांक_reg(s, winकरोw, VREG(LRX_WCRED));
	prपूर्णांक_reg(s, winकरोw, VREG(LRX_WCRED_ADDER));
	prपूर्णांक_reg(s, winकरोw, VREG(TX_WCRED));
	prपूर्णांक_reg(s, winकरोw, VREG(TX_WCRED_ADDER));
	prपूर्णांक_reg(s, winकरोw, VREG(LFIFO_SIZE));
	prपूर्णांक_reg(s, winकरोw, VREG(WINCTL));
	prपूर्णांक_reg(s, winकरोw, VREG(WIN_STATUS));
	prपूर्णांक_reg(s, winकरोw, VREG(WIN_CTX_CACHING_CTL));
	prपूर्णांक_reg(s, winकरोw, VREG(TX_RSVD_BUF_COUNT));
	prपूर्णांक_reg(s, winकरोw, VREG(LRFIFO_WIN_PTR));
	prपूर्णांक_reg(s, winकरोw, VREG(LNOTIFY_CTL));
	prपूर्णांक_reg(s, winकरोw, VREG(LNOTIFY_PID));
	prपूर्णांक_reg(s, winकरोw, VREG(LNOTIFY_LPID));
	prपूर्णांक_reg(s, winकरोw, VREG(LNOTIFY_TID));
	prपूर्णांक_reg(s, winकरोw, VREG(LNOTIFY_SCOPE));
	prपूर्णांक_reg(s, winकरोw, VREG(NX_UTIL_ADDER));
unlock:
	mutex_unlock(&vas_mutex);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(hvwc);

व्योम vas_winकरोw_मुक्त_dbgdir(काष्ठा vas_winकरोw *winकरोw)
अणु
	अगर (winकरोw->dbgdir) अणु
		debugfs_हटाओ_recursive(winकरोw->dbgdir);
		kमुक्त(winकरोw->dbgname);
		winकरोw->dbgdir = शून्य;
		winकरोw->dbgname = शून्य;
	पूर्ण
पूर्ण

व्योम vas_winकरोw_init_dbgdir(काष्ठा vas_winकरोw *winकरोw)
अणु
	काष्ठा dentry *d;

	अगर (!winकरोw->vinst->dbgdir)
		वापस;

	winकरोw->dbgname = kzalloc(16, GFP_KERNEL);
	अगर (!winकरोw->dbgname)
		वापस;

	snम_लिखो(winकरोw->dbgname, 16, "w%d", winकरोw->winid);

	d = debugfs_create_dir(winकरोw->dbgname, winकरोw->vinst->dbgdir);
	winकरोw->dbgdir = d;

	debugfs_create_file("info", 0444, d, winकरोw, &info_fops);
	debugfs_create_file("hvwc", 0444, d, winकरोw, &hvwc_fops);
पूर्ण

व्योम vas_instance_init_dbgdir(काष्ठा vas_instance *vinst)
अणु
	काष्ठा dentry *d;

	vas_init_dbgdir();

	vinst->dbgname = kzalloc(16, GFP_KERNEL);
	अगर (!vinst->dbgname)
		वापस;

	snम_लिखो(vinst->dbgname, 16, "v%d", vinst->vas_id);

	d = debugfs_create_dir(vinst->dbgname, vas_debugfs);
	vinst->dbgdir = d;
पूर्ण

/*
 * Set up the "root" VAS debugfs dir. Return अगर we alपढ़ोy set it up
 * (or failed to) in an earlier instance of VAS.
 */
व्योम vas_init_dbgdir(व्योम)
अणु
	अटल bool first_समय = true;

	अगर (!first_समय)
		वापस;

	first_समय = false;
	vas_debugfs = debugfs_create_dir("vas", शून्य);
पूर्ण
