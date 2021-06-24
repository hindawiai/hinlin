<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016-17 IBM Corp.
 */

#अगर_अघोषित _ASM_POWERPC_VAS_H
#घोषणा _ASM_POWERPC_VAS_H

काष्ठा vas_winकरोw;

/*
 * Min and max FIFO sizes are based on Version 1.05 Section 3.1.4.25
 * (Local FIFO Size Register) of the VAS workbook.
 */
#घोषणा VAS_RX_FIFO_SIZE_MIN	(1 << 10)	/* 1KB */
#घोषणा VAS_RX_FIFO_SIZE_MAX	(8 << 20)	/* 8MB */

/*
 * Threshold Control Mode: Have paste operation fail अगर the number of
 * requests in receive FIFO exceeds a threshold.
 *
 * NOTE: No special error code yet अगर paste is rejected because of these
 *	 limits. So users can't distinguish between this and other errors.
 */
#घोषणा VAS_THRESH_DISABLED		0
#घोषणा VAS_THRESH_FIFO_GT_HALF_FULL	1
#घोषणा VAS_THRESH_FIFO_GT_QTR_FULL	2
#घोषणा VAS_THRESH_FIFO_GT_EIGHTH_FULL	3

/*
 * Get/Set bit fields
 */
#घोषणा GET_FIELD(m, v)                (((v) & (m)) >> MASK_LSH(m))
#घोषणा MASK_LSH(m)            (__builtin_ffsl(m) - 1)
#घोषणा SET_FIELD(m, v, val)   \
		(((v) & ~(m)) | ((((typeof(v))(val)) << MASK_LSH(m)) & (m)))

/*
 * Co-processor Engine type.
 */
क्रमागत vas_cop_type अणु
	VAS_COP_TYPE_FAULT,
	VAS_COP_TYPE_842,
	VAS_COP_TYPE_842_HIPRI,
	VAS_COP_TYPE_GZIP,
	VAS_COP_TYPE_GZIP_HIPRI,
	VAS_COP_TYPE_FTW,
	VAS_COP_TYPE_MAX,
पूर्ण;

/*
 * Receive winकरोw attributes specअगरied by the (in-kernel) owner of winकरोw.
 */
काष्ठा vas_rx_win_attr अणु
	व्योम *rx_fअगरo;
	पूर्णांक rx_fअगरo_size;
	पूर्णांक wcreds_max;

	bool pin_win;
	bool rej_no_credit;
	bool tx_wcred_mode;
	bool rx_wcred_mode;
	bool tx_win_ord_mode;
	bool rx_win_ord_mode;
	bool data_stamp;
	bool nx_win;
	bool fault_win;
	bool user_win;
	bool notअगरy_disable;
	bool पूर्णांकr_disable;
	bool notअगरy_early;

	पूर्णांक lnotअगरy_lpid;
	पूर्णांक lnotअगरy_pid;
	पूर्णांक lnotअगरy_tid;
	u32 pswid;

	पूर्णांक tc_mode;
पूर्ण;

/*
 * Winकरोw attributes specअगरied by the in-kernel owner of a send winकरोw.
 */
काष्ठा vas_tx_win_attr अणु
	क्रमागत vas_cop_type cop;
	पूर्णांक wcreds_max;
	पूर्णांक lpid;
	पूर्णांक pidr;		/* hardware PID (from SPRN_PID) */
	पूर्णांक pswid;
	पूर्णांक rsvd_txbuf_count;
	पूर्णांक tc_mode;

	bool user_win;
	bool pin_win;
	bool rej_no_credit;
	bool rsvd_txbuf_enable;
	bool tx_wcred_mode;
	bool rx_wcred_mode;
	bool tx_win_ord_mode;
	bool rx_win_ord_mode;
पूर्ण;

/*
 * Helper to map a chip id to VAS id.
 * For POWER9, this is a 1:1 mapping. In the future this maybe a 1:N
 * mapping in which हाल, we will need to update this helper.
 *
 * Return the VAS id or -1 अगर no matching vasid is found.
 */
पूर्णांक chip_to_vas_id(पूर्णांक chipid);

/*
 * Helper to initialize receive winकरोw attributes to शेषs क्रम an
 * NX winकरोw.
 */
व्योम vas_init_rx_win_attr(काष्ठा vas_rx_win_attr *rxattr, क्रमागत vas_cop_type cop);

/*
 * Open a VAS receive winकरोw क्रम the instance of VAS identअगरied by @vasid
 * Use @attr to initialize the attributes of the winकरोw.
 *
 * Return a handle to the winकरोw or ERR_PTR() on error.
 */
काष्ठा vas_winकरोw *vas_rx_win_खोलो(पूर्णांक vasid, क्रमागत vas_cop_type cop,
				   काष्ठा vas_rx_win_attr *attr);

/*
 * Helper to initialize send winकरोw attributes to शेषs क्रम an NX winकरोw.
 */
बाह्य व्योम vas_init_tx_win_attr(काष्ठा vas_tx_win_attr *txattr,
			क्रमागत vas_cop_type cop);

/*
 * Open a VAS send winकरोw क्रम the instance of VAS identअगरied by @vasid
 * and the co-processor type @cop. Use @attr to initialize attributes
 * of the winकरोw.
 *
 * Note: The instance of VAS must alपढ़ोy have an खोलो receive winकरोw क्रम
 * the coprocessor type @cop.
 *
 * Return a handle to the send winकरोw or ERR_PTR() on error.
 */
काष्ठा vas_winकरोw *vas_tx_win_खोलो(पूर्णांक vasid, क्रमागत vas_cop_type cop,
			काष्ठा vas_tx_win_attr *attr);

/*
 * Close the send or receive winकरोw identअगरied by @win. For receive winकरोws
 * वापस -EAGAIN अगर there are active send winकरोws attached to this receive
 * winकरोw.
 */
पूर्णांक vas_win_बंद(काष्ठा vas_winकरोw *win);

/*
 * Copy the co-processor request block (CRB) @crb पूर्णांकo the local L2 cache.
 */
पूर्णांक vas_copy_crb(व्योम *crb, पूर्णांक offset);

/*
 * Paste a previously copied CRB (see vas_copy_crb()) from the L2 cache to
 * the hardware address associated with the winकरोw @win. @re is expected/
 * assumed to be true क्रम NX winकरोws.
 */
पूर्णांक vas_paste_crb(काष्ठा vas_winकरोw *win, पूर्णांक offset, bool re);

/*
 * Register / unरेजिस्टर coprocessor type to VAS API which will be exported
 * to user space. Applications can use this API to खोलो / बंद winकरोw
 * which can be used to send / receive requests directly to cooprcessor.
 *
 * Only NX GZIP coprocessor type is supported now, but this API can be
 * used क्रम others in future.
 */
पूर्णांक vas_रेजिस्टर_coproc_api(काष्ठा module *mod, क्रमागत vas_cop_type cop_type,
				स्थिर अक्षर *name);
व्योम vas_unरेजिस्टर_coproc_api(व्योम);

#पूर्ण_अगर /* __ASM_POWERPC_VAS_H */
