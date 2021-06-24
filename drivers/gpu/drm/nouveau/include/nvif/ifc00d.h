<शैली गुरु>
#अगर_अघोषित __NVIF_IFC00D_H__
#घोषणा __NVIF_IFC00D_H__
#समावेश "if000c.h"

काष्ठा gp100_vmm_vn अणु
	/* nvअगर_vmm_vX ... */
पूर्ण;

काष्ठा gp100_vmm_v0 अणु
	/* nvअगर_vmm_vX ... */
	__u8  version;
	__u8  fault_replay;
पूर्ण;

काष्ठा gp100_vmm_map_vn अणु
	/* nvअगर_vmm_map_vX ... */
पूर्ण;

काष्ठा gp100_vmm_map_v0 अणु
	/* nvअगर_vmm_map_vX ... */
	__u8  version;
	__u8  vol;
	__u8  ro;
	__u8  priv;
	__u8  kind;
पूर्ण;

#घोषणा GP100_VMM_VN_FAULT_REPLAY                         NVIF_VMM_V0_MTHD(0x00)
#घोषणा GP100_VMM_VN_FAULT_CANCEL                         NVIF_VMM_V0_MTHD(0x01)

काष्ठा gp100_vmm_fault_replay_vn अणु
पूर्ण;

काष्ठा gp100_vmm_fault_cancel_v0 अणु
	__u8  version;
	__u8  hub;
	__u8  gpc;
	__u8  client;
	__u8  pad04[4];
	__u64 inst;
पूर्ण;
#पूर्ण_अगर
