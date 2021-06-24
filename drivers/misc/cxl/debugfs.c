<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "cxl.h"

अटल काष्ठा dentry *cxl_debugfs;

/* Helpers to export CXL mmaped IO रेजिस्टरs via debugfs */
अटल पूर्णांक debugfs_io_u64_get(व्योम *data, u64 *val)
अणु
	*val = in_be64((u64 __iomem *)data);
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_io_u64_set(व्योम *data, u64 val)
अणु
	out_be64((u64 __iomem *)data, val);
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_io_x64, debugfs_io_u64_get, debugfs_io_u64_set,
			 "0x%016llx\n");

अटल व्योम debugfs_create_io_x64(स्थिर अक्षर *name, umode_t mode,
				  काष्ठा dentry *parent, u64 __iomem *value)
अणु
	debugfs_create_file_unsafe(name, mode, parent, (व्योम __क्रमce *)value,
				   &fops_io_x64);
पूर्ण

व्योम cxl_debugfs_add_adapter_regs_psl9(काष्ठा cxl *adapter, काष्ठा dentry *dir)
अणु
	debugfs_create_io_x64("fir1", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL9_FIR1));
	debugfs_create_io_x64("fir_mask", 0400, dir,
			      _cxl_p1_addr(adapter, CXL_PSL9_FIR_MASK));
	debugfs_create_io_x64("fir_cntl", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL9_FIR_CNTL));
	debugfs_create_io_x64("trace", S_IRUSR | S_IWUSR, dir, _cxl_p1_addr(adapter, CXL_PSL9_TRACECFG));
	debugfs_create_io_x64("debug", 0600, dir,
			      _cxl_p1_addr(adapter, CXL_PSL9_DEBUG));
	debugfs_create_io_x64("xsl-debug", 0600, dir,
			      _cxl_p1_addr(adapter, CXL_XSL9_DBG));
पूर्ण

व्योम cxl_debugfs_add_adapter_regs_psl8(काष्ठा cxl *adapter, काष्ठा dentry *dir)
अणु
	debugfs_create_io_x64("fir1", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_FIR1));
	debugfs_create_io_x64("fir2", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_FIR2));
	debugfs_create_io_x64("fir_cntl", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_FIR_CNTL));
	debugfs_create_io_x64("trace", S_IRUSR | S_IWUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_TRACE));
पूर्ण

व्योम cxl_debugfs_adapter_add(काष्ठा cxl *adapter)
अणु
	काष्ठा dentry *dir;
	अक्षर buf[32];

	अगर (!cxl_debugfs)
		वापस;

	snम_लिखो(buf, 32, "card%i", adapter->adapter_num);
	dir = debugfs_create_dir(buf, cxl_debugfs);
	adapter->debugfs = dir;

	debugfs_create_io_x64("err_ivte", S_IRUSR, dir, _cxl_p1_addr(adapter, CXL_PSL_ErrIVTE));

	अगर (adapter->native->sl_ops->debugfs_add_adapter_regs)
		adapter->native->sl_ops->debugfs_add_adapter_regs(adapter, dir);
पूर्ण

व्योम cxl_debugfs_adapter_हटाओ(काष्ठा cxl *adapter)
अणु
	debugfs_हटाओ_recursive(adapter->debugfs);
पूर्ण

व्योम cxl_debugfs_add_afu_regs_psl9(काष्ठा cxl_afu *afu, काष्ठा dentry *dir)
अणु
	debugfs_create_io_x64("serr", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SERR_An));
पूर्ण

व्योम cxl_debugfs_add_afu_regs_psl8(काष्ठा cxl_afu *afu, काष्ठा dentry *dir)
अणु
	debugfs_create_io_x64("sstp0", S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_SSTP0_An));
	debugfs_create_io_x64("sstp1", S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_SSTP1_An));

	debugfs_create_io_x64("fir", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_FIR_SLICE_An));
	debugfs_create_io_x64("serr", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SERR_An));
	debugfs_create_io_x64("afu_debug", S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_AFU_DEBUG_An));
	debugfs_create_io_x64("trace", S_IRUSR | S_IWUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SLICE_TRACE));
पूर्ण

व्योम cxl_debugfs_afu_add(काष्ठा cxl_afu *afu)
अणु
	काष्ठा dentry *dir;
	अक्षर buf[32];

	अगर (!afu->adapter->debugfs)
		वापस;

	snम_लिखो(buf, 32, "psl%i.%i", afu->adapter->adapter_num, afu->slice);
	dir = debugfs_create_dir(buf, afu->adapter->debugfs);
	afu->debugfs = dir;

	debugfs_create_io_x64("sr",         S_IRUSR, dir, _cxl_p1n_addr(afu, CXL_PSL_SR_An));
	debugfs_create_io_x64("dsisr",      S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_PSL_DSISR_An));
	debugfs_create_io_x64("dar",        S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_PSL_DAR_An));

	debugfs_create_io_x64("err_status", S_IRUSR, dir, _cxl_p2n_addr(afu, CXL_PSL_ErrStat_An));

	अगर (afu->adapter->native->sl_ops->debugfs_add_afu_regs)
		afu->adapter->native->sl_ops->debugfs_add_afu_regs(afu, dir);
पूर्ण

व्योम cxl_debugfs_afu_हटाओ(काष्ठा cxl_afu *afu)
अणु
	debugfs_हटाओ_recursive(afu->debugfs);
पूर्ण

व्योम __init cxl_debugfs_init(व्योम)
अणु
	अगर (!cpu_has_feature(CPU_FTR_HVMODE))
		वापस;

	cxl_debugfs = debugfs_create_dir("cxl", शून्य);
पूर्ण

व्योम cxl_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(cxl_debugfs);
पूर्ण
