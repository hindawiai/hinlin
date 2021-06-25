<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _GUARDED_STORAGE_H
#घोषणा _GUARDED_STORAGE_H

#समावेश <linux/types.h>

काष्ठा gs_cb अणु
	__u64 reserved;
	__u64 gsd;
	__u64 gssm;
	__u64 gs_epl_a;
पूर्ण;

काष्ठा gs_epl अणु
	__u8 pad1;
	जोड़ अणु
		__u8 gs_eam;
		काष्ठा अणु
			__u8	: 6;
			__u8 e	: 1;
			__u8 b	: 1;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		__u8 gs_eci;
		काष्ठा अणु
			__u8 tx	: 1;
			__u8 cx	: 1;
			__u8	: 5;
			__u8 in	: 1;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		__u8 gs_eai;
		काष्ठा अणु
			__u8	: 1;
			__u8 t	: 1;
			__u8 as	: 2;
			__u8 ar	: 4;
		पूर्ण;
	पूर्ण;
	__u32 pad2;
	__u64 gs_eha;
	__u64 gs_eia;
	__u64 gs_eoa;
	__u64 gs_eir;
	__u64 gs_era;
पूर्ण;

#घोषणा GS_ENABLE	0
#घोषणा	GS_DISABLE	1
#घोषणा GS_SET_BC_CB	2
#घोषणा GS_CLEAR_BC_CB	3
#घोषणा GS_BROADCAST	4

अटल अंतरभूत व्योम load_gs_cb(काष्ठा gs_cb *gs_cb)
अणु
	यंत्र अस्थिर(".insn rxy,0xe3000000004d,0,%0" : : "Q" (*gs_cb));
पूर्ण

अटल अंतरभूत व्योम store_gs_cb(काष्ठा gs_cb *gs_cb)
अणु
	यंत्र अस्थिर(".insn rxy,0xe30000000049,0,%0" : : "Q" (*gs_cb));
पूर्ण

अटल अंतरभूत व्योम save_gs_cb(काष्ठा gs_cb *gs_cb)
अणु
	अगर (gs_cb)
		store_gs_cb(gs_cb);
पूर्ण

अटल अंतरभूत व्योम restore_gs_cb(काष्ठा gs_cb *gs_cb)
अणु
	अगर (gs_cb)
		load_gs_cb(gs_cb);
पूर्ण

#पूर्ण_अगर /* _GUARDED_STORAGE_H */
