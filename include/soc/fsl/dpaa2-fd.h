<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 *
 */
#अगर_अघोषित __FSL_DPAA2_FD_H
#घोषणा __FSL_DPAA2_FD_H

#समावेश <linux/kernel.h>

/**
 * DOC: DPAA2 FD - Frame Descriptor APIs क्रम DPAA2
 *
 * Frame Descriptors (FDs) are used to describe frame data in the DPAA2.
 * Frames can be enqueued and dequeued to Frame Queues (FQs) which are consumed
 * by the various DPAA accelerators (WRIOP, SEC, PME, DCE)
 *
 * There are three types of frames: single, scatter gather, and frame lists.
 *
 * The set of APIs in this file must be used to create, manipulate and
 * query Frame Descriptors.
 */

/**
 * काष्ठा dpaa2_fd - Struct describing FDs
 * @words:         क्रम easier/faster copying the whole FD काष्ठाure
 * @addr:          address in the FD
 * @len:           length in the FD
 * @bpid:          buffer pool ID
 * @क्रमmat_offset: क्रमmat, offset, and लघु-length fields
 * @frc:           frame context
 * @ctrl:          control bits...including dd, sc, va, err, etc
 * @flc:           flow context address
 *
 * This काष्ठाure represents the basic Frame Descriptor used in the प्रणाली.
 */
काष्ठा dpaa2_fd अणु
	जोड़ अणु
		u32 words[8];
		काष्ठा dpaa2_fd_simple अणु
			__le64 addr;
			__le32 len;
			__le16 bpid;
			__le16 क्रमmat_offset;
			__le32 frc;
			__le32 ctrl;
			__le64 flc;
		पूर्ण simple;
	पूर्ण;
पूर्ण;

#घोषणा FD_SHORT_LEN_FLAG_MASK	0x1
#घोषणा FD_SHORT_LEN_FLAG_SHIFT	14
#घोषणा FD_SHORT_LEN_MASK	0x3FFFF
#घोषणा FD_OFFSET_MASK		0x0FFF
#घोषणा FD_FORMAT_MASK		0x3
#घोषणा FD_FORMAT_SHIFT		12
#घोषणा FD_BPID_MASK		0x3FFF
#घोषणा SG_SHORT_LEN_FLAG_MASK	0x1
#घोषणा SG_SHORT_LEN_FLAG_SHIFT	14
#घोषणा SG_SHORT_LEN_MASK	0x1FFFF
#घोषणा SG_OFFSET_MASK		0x0FFF
#घोषणा SG_FORMAT_MASK		0x3
#घोषणा SG_FORMAT_SHIFT		12
#घोषणा SG_BPID_MASK		0x3FFF
#घोषणा SG_FINAL_FLAG_MASK	0x1
#घोषणा SG_FINAL_FLAG_SHIFT	15
#घोषणा FL_SHORT_LEN_FLAG_MASK	0x1
#घोषणा FL_SHORT_LEN_FLAG_SHIFT	14
#घोषणा FL_SHORT_LEN_MASK	0x3FFFF
#घोषणा FL_OFFSET_MASK		0x0FFF
#घोषणा FL_FORMAT_MASK		0x3
#घोषणा FL_FORMAT_SHIFT		12
#घोषणा FL_BPID_MASK		0x3FFF
#घोषणा FL_FINAL_FLAG_MASK	0x1
#घोषणा FL_FINAL_FLAG_SHIFT	15

/* Error bits in FD CTRL */
#घोषणा FD_CTRL_ERR_MASK	0x000000FF
#घोषणा FD_CTRL_UFD		0x00000004
#घोषणा FD_CTRL_SBE		0x00000008
#घोषणा FD_CTRL_FLC		0x00000010
#घोषणा FD_CTRL_FSE		0x00000020
#घोषणा FD_CTRL_FAERR		0x00000040

/* Annotation bits in FD CTRL */
#घोषणा FD_CTRL_PTA		0x00800000
#घोषणा FD_CTRL_PTV1		0x00400000

क्रमागत dpaa2_fd_क्रमmat अणु
	dpaa2_fd_single = 0,
	dpaa2_fd_list,
	dpaa2_fd_sg
पूर्ण;

/**
 * dpaa2_fd_get_addr() - get the addr field of frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the address in the frame descriptor.
 */
अटल अंतरभूत dma_addr_t dpaa2_fd_get_addr(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस (dma_addr_t)le64_to_cpu(fd->simple.addr);
पूर्ण

/**
 * dpaa2_fd_set_addr() - Set the addr field of frame descriptor
 * @fd: the given frame descriptor
 * @addr: the address needs to be set in frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_addr(काष्ठा dpaa2_fd *fd, dma_addr_t addr)
अणु
	fd->simple.addr = cpu_to_le64(addr);
पूर्ण

/**
 * dpaa2_fd_get_frc() - Get the frame context in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the frame context field in the frame descriptor.
 */
अटल अंतरभूत u32 dpaa2_fd_get_frc(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस le32_to_cpu(fd->simple.frc);
पूर्ण

/**
 * dpaa2_fd_set_frc() - Set the frame context in the frame descriptor
 * @fd: the given frame descriptor
 * @frc: the frame context needs to be set in frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_frc(काष्ठा dpaa2_fd *fd, u32 frc)
अणु
	fd->simple.frc = cpu_to_le32(frc);
पूर्ण

/**
 * dpaa2_fd_get_ctrl() - Get the control bits in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the control bits field in the frame descriptor.
 */
अटल अंतरभूत u32 dpaa2_fd_get_ctrl(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस le32_to_cpu(fd->simple.ctrl);
पूर्ण

/**
 * dpaa2_fd_set_ctrl() - Set the control bits in the frame descriptor
 * @fd: the given frame descriptor
 * @ctrl: the control bits to be set in the frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_ctrl(काष्ठा dpaa2_fd *fd, u32 ctrl)
अणु
	fd->simple.ctrl = cpu_to_le32(ctrl);
पूर्ण

/**
 * dpaa2_fd_get_flc() - Get the flow context in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the flow context in the frame descriptor.
 */
अटल अंतरभूत dma_addr_t dpaa2_fd_get_flc(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस (dma_addr_t)le64_to_cpu(fd->simple.flc);
पूर्ण

/**
 * dpaa2_fd_set_flc() - Set the flow context field of frame descriptor
 * @fd: the given frame descriptor
 * @flc_addr: the flow context needs to be set in frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_flc(काष्ठा dpaa2_fd *fd,  dma_addr_t flc_addr)
अणु
	fd->simple.flc = cpu_to_le64(flc_addr);
पूर्ण

अटल अंतरभूत bool dpaa2_fd_लघु_len(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस !!((le16_to_cpu(fd->simple.क्रमmat_offset) >>
		  FD_SHORT_LEN_FLAG_SHIFT) & FD_SHORT_LEN_FLAG_MASK);
पूर्ण

/**
 * dpaa2_fd_get_len() - Get the length in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the length field in the frame descriptor.
 */
अटल अंतरभूत u32 dpaa2_fd_get_len(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	अगर (dpaa2_fd_लघु_len(fd))
		वापस le32_to_cpu(fd->simple.len) & FD_SHORT_LEN_MASK;

	वापस le32_to_cpu(fd->simple.len);
पूर्ण

/**
 * dpaa2_fd_set_len() - Set the length field of frame descriptor
 * @fd: the given frame descriptor
 * @len: the length needs to be set in frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_len(काष्ठा dpaa2_fd *fd, u32 len)
अणु
	fd->simple.len = cpu_to_le32(len);
पूर्ण

/**
 * dpaa2_fd_get_offset() - Get the offset field in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the offset.
 */
अटल अंतरभूत uपूर्णांक16_t dpaa2_fd_get_offset(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस le16_to_cpu(fd->simple.क्रमmat_offset) & FD_OFFSET_MASK;
पूर्ण

/**
 * dpaa2_fd_set_offset() - Set the offset field of frame descriptor
 * @fd: the given frame descriptor
 * @offset: the offset needs to be set in frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_offset(काष्ठा dpaa2_fd *fd, uपूर्णांक16_t offset)
अणु
	fd->simple.क्रमmat_offset &= cpu_to_le16(~FD_OFFSET_MASK);
	fd->simple.क्रमmat_offset |= cpu_to_le16(offset);
पूर्ण

/**
 * dpaa2_fd_get_क्रमmat() - Get the क्रमmat field in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the क्रमmat.
 */
अटल अंतरभूत क्रमागत dpaa2_fd_क्रमmat dpaa2_fd_get_क्रमmat(
						स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस (क्रमागत dpaa2_fd_क्रमmat)((le16_to_cpu(fd->simple.क्रमmat_offset)
				      >> FD_FORMAT_SHIFT) & FD_FORMAT_MASK);
पूर्ण

/**
 * dpaa2_fd_set_क्रमmat() - Set the क्रमmat field of frame descriptor
 * @fd: the given frame descriptor
 * @क्रमmat: the क्रमmat needs to be set in frame descriptor
 */
अटल अंतरभूत व्योम dpaa2_fd_set_क्रमmat(काष्ठा dpaa2_fd *fd,
				       क्रमागत dpaa2_fd_क्रमmat क्रमmat)
अणु
	fd->simple.क्रमmat_offset &=
		cpu_to_le16(~(FD_FORMAT_MASK << FD_FORMAT_SHIFT));
	fd->simple.क्रमmat_offset |= cpu_to_le16(क्रमmat << FD_FORMAT_SHIFT);
पूर्ण

/**
 * dpaa2_fd_get_bpid() - Get the bpid field in the frame descriptor
 * @fd: the given frame descriptor
 *
 * Return the buffer pool id.
 */
अटल अंतरभूत uपूर्णांक16_t dpaa2_fd_get_bpid(स्थिर काष्ठा dpaa2_fd *fd)
अणु
	वापस le16_to_cpu(fd->simple.bpid) & FD_BPID_MASK;
पूर्ण

/**
 * dpaa2_fd_set_bpid() - Set the bpid field of frame descriptor
 * @fd: the given frame descriptor
 * @bpid: buffer pool id to be set
 */
अटल अंतरभूत व्योम dpaa2_fd_set_bpid(काष्ठा dpaa2_fd *fd, uपूर्णांक16_t bpid)
अणु
	fd->simple.bpid &= cpu_to_le16(~(FD_BPID_MASK));
	fd->simple.bpid |= cpu_to_le16(bpid);
पूर्ण

/**
 * काष्ठा dpaa2_sg_entry - the scatter-gathering काष्ठाure
 * @addr: address of the sg entry
 * @len: length in this sg entry
 * @bpid: buffer pool id
 * @क्रमmat_offset: क्रमmat and offset fields
 */
काष्ठा dpaa2_sg_entry अणु
	__le64 addr;
	__le32 len;
	__le16 bpid;
	__le16 क्रमmat_offset;
पूर्ण;

क्रमागत dpaa2_sg_क्रमmat अणु
	dpaa2_sg_single = 0,
	dpaa2_sg_frame_data,
	dpaa2_sg_sgt_ext
पूर्ण;

/* Accessors क्रम SG entry fields */

/**
 * dpaa2_sg_get_addr() - Get the address from SG entry
 * @sg: the given scatter-gathering object
 *
 * Return the address.
 */
अटल अंतरभूत dma_addr_t dpaa2_sg_get_addr(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	वापस (dma_addr_t)le64_to_cpu(sg->addr);
पूर्ण

/**
 * dpaa2_sg_set_addr() - Set the address in SG entry
 * @sg: the given scatter-gathering object
 * @addr: the address to be set
 */
अटल अंतरभूत व्योम dpaa2_sg_set_addr(काष्ठा dpaa2_sg_entry *sg, dma_addr_t addr)
अणु
	sg->addr = cpu_to_le64(addr);
पूर्ण

अटल अंतरभूत bool dpaa2_sg_लघु_len(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	वापस !!((le16_to_cpu(sg->क्रमmat_offset) >> SG_SHORT_LEN_FLAG_SHIFT)
		& SG_SHORT_LEN_FLAG_MASK);
पूर्ण

/**
 * dpaa2_sg_get_len() - Get the length in SG entry
 * @sg: the given scatter-gathering object
 *
 * Return the length.
 */
अटल अंतरभूत u32 dpaa2_sg_get_len(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	अगर (dpaa2_sg_लघु_len(sg))
		वापस le32_to_cpu(sg->len) & SG_SHORT_LEN_MASK;

	वापस le32_to_cpu(sg->len);
पूर्ण

/**
 * dpaa2_sg_set_len() - Set the length in SG entry
 * @sg: the given scatter-gathering object
 * @len: the length to be set
 */
अटल अंतरभूत व्योम dpaa2_sg_set_len(काष्ठा dpaa2_sg_entry *sg, u32 len)
अणु
	sg->len = cpu_to_le32(len);
पूर्ण

/**
 * dpaa2_sg_get_offset() - Get the offset in SG entry
 * @sg: the given scatter-gathering object
 *
 * Return the offset.
 */
अटल अंतरभूत u16 dpaa2_sg_get_offset(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	वापस le16_to_cpu(sg->क्रमmat_offset) & SG_OFFSET_MASK;
पूर्ण

/**
 * dpaa2_sg_set_offset() - Set the offset in SG entry
 * @sg: the given scatter-gathering object
 * @offset: the offset to be set
 */
अटल अंतरभूत व्योम dpaa2_sg_set_offset(काष्ठा dpaa2_sg_entry *sg,
				       u16 offset)
अणु
	sg->क्रमmat_offset &= cpu_to_le16(~SG_OFFSET_MASK);
	sg->क्रमmat_offset |= cpu_to_le16(offset);
पूर्ण

/**
 * dpaa2_sg_get_क्रमmat() - Get the SG क्रमmat in SG entry
 * @sg: the given scatter-gathering object
 *
 * Return the क्रमmat.
 */
अटल अंतरभूत क्रमागत dpaa2_sg_क्रमmat
	dpaa2_sg_get_क्रमmat(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	वापस (क्रमागत dpaa2_sg_क्रमmat)((le16_to_cpu(sg->क्रमmat_offset)
				       >> SG_FORMAT_SHIFT) & SG_FORMAT_MASK);
पूर्ण

/**
 * dpaa2_sg_set_क्रमmat() - Set the SG क्रमmat in SG entry
 * @sg: the given scatter-gathering object
 * @क्रमmat: the क्रमmat to be set
 */
अटल अंतरभूत व्योम dpaa2_sg_set_क्रमmat(काष्ठा dpaa2_sg_entry *sg,
				       क्रमागत dpaa2_sg_क्रमmat क्रमmat)
अणु
	sg->क्रमmat_offset &= cpu_to_le16(~(SG_FORMAT_MASK << SG_FORMAT_SHIFT));
	sg->क्रमmat_offset |= cpu_to_le16(क्रमmat << SG_FORMAT_SHIFT);
पूर्ण

/**
 * dpaa2_sg_get_bpid() - Get the buffer pool id in SG entry
 * @sg: the given scatter-gathering object
 *
 * Return the bpid.
 */
अटल अंतरभूत u16 dpaa2_sg_get_bpid(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	वापस le16_to_cpu(sg->bpid) & SG_BPID_MASK;
पूर्ण

/**
 * dpaa2_sg_set_bpid() - Set the buffer pool id in SG entry
 * @sg: the given scatter-gathering object
 * @bpid: the bpid to be set
 */
अटल अंतरभूत व्योम dpaa2_sg_set_bpid(काष्ठा dpaa2_sg_entry *sg, u16 bpid)
अणु
	sg->bpid &= cpu_to_le16(~(SG_BPID_MASK));
	sg->bpid |= cpu_to_le16(bpid);
पूर्ण

/**
 * dpaa2_sg_is_final() - Check final bit in SG entry
 * @sg: the given scatter-gathering object
 *
 * Return bool.
 */
अटल अंतरभूत bool dpaa2_sg_is_final(स्थिर काष्ठा dpaa2_sg_entry *sg)
अणु
	वापस !!(le16_to_cpu(sg->क्रमmat_offset) >> SG_FINAL_FLAG_SHIFT);
पूर्ण

/**
 * dpaa2_sg_set_final() - Set the final bit in SG entry
 * @sg: the given scatter-gathering object
 * @final: the final boolean to be set
 */
अटल अंतरभूत व्योम dpaa2_sg_set_final(काष्ठा dpaa2_sg_entry *sg, bool final)
अणु
	sg->क्रमmat_offset &= cpu_to_le16((~(SG_FINAL_FLAG_MASK
					 << SG_FINAL_FLAG_SHIFT)) & 0xFFFF);
	sg->क्रमmat_offset |= cpu_to_le16(final << SG_FINAL_FLAG_SHIFT);
पूर्ण

/**
 * काष्ठा dpaa2_fl_entry - काष्ठाure क्रम frame list entry.
 * @addr:          address in the FLE
 * @len:           length in the FLE
 * @bpid:          buffer pool ID
 * @क्रमmat_offset: क्रमmat, offset, and लघु-length fields
 * @frc:           frame context
 * @ctrl:          control bits...including pta, pvt1, pvt2, err, etc
 * @flc:           flow context address
 */
काष्ठा dpaa2_fl_entry अणु
	__le64 addr;
	__le32 len;
	__le16 bpid;
	__le16 क्रमmat_offset;
	__le32 frc;
	__le32 ctrl;
	__le64 flc;
पूर्ण;

क्रमागत dpaa2_fl_क्रमmat अणु
	dpaa2_fl_single = 0,
	dpaa2_fl_res,
	dpaa2_fl_sg
पूर्ण;

/**
 * dpaa2_fl_get_addr() - get the addr field of FLE
 * @fle: the given frame list entry
 *
 * Return the address in the frame list entry.
 */
अटल अंतरभूत dma_addr_t dpaa2_fl_get_addr(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस (dma_addr_t)le64_to_cpu(fle->addr);
पूर्ण

/**
 * dpaa2_fl_set_addr() - Set the addr field of FLE
 * @fle: the given frame list entry
 * @addr: the address needs to be set in frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_addr(काष्ठा dpaa2_fl_entry *fle,
				     dma_addr_t addr)
अणु
	fle->addr = cpu_to_le64(addr);
पूर्ण

/**
 * dpaa2_fl_get_frc() - Get the frame context in the FLE
 * @fle: the given frame list entry
 *
 * Return the frame context field in the frame lsit entry.
 */
अटल अंतरभूत u32 dpaa2_fl_get_frc(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस le32_to_cpu(fle->frc);
पूर्ण

/**
 * dpaa2_fl_set_frc() - Set the frame context in the FLE
 * @fle: the given frame list entry
 * @frc: the frame context needs to be set in frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_frc(काष्ठा dpaa2_fl_entry *fle, u32 frc)
अणु
	fle->frc = cpu_to_le32(frc);
पूर्ण

/**
 * dpaa2_fl_get_ctrl() - Get the control bits in the FLE
 * @fle: the given frame list entry
 *
 * Return the control bits field in the frame list entry.
 */
अटल अंतरभूत u32 dpaa2_fl_get_ctrl(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस le32_to_cpu(fle->ctrl);
पूर्ण

/**
 * dpaa2_fl_set_ctrl() - Set the control bits in the FLE
 * @fle: the given frame list entry
 * @ctrl: the control bits to be set in the frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_ctrl(काष्ठा dpaa2_fl_entry *fle, u32 ctrl)
अणु
	fle->ctrl = cpu_to_le32(ctrl);
पूर्ण

/**
 * dpaa2_fl_get_flc() - Get the flow context in the FLE
 * @fle: the given frame list entry
 *
 * Return the flow context in the frame list entry.
 */
अटल अंतरभूत dma_addr_t dpaa2_fl_get_flc(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस (dma_addr_t)le64_to_cpu(fle->flc);
पूर्ण

/**
 * dpaa2_fl_set_flc() - Set the flow context field of FLE
 * @fle: the given frame list entry
 * @flc_addr: the flow context needs to be set in frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_flc(काष्ठा dpaa2_fl_entry *fle,
				    dma_addr_t flc_addr)
अणु
	fle->flc = cpu_to_le64(flc_addr);
पूर्ण

अटल अंतरभूत bool dpaa2_fl_लघु_len(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस !!((le16_to_cpu(fle->क्रमmat_offset) >>
		  FL_SHORT_LEN_FLAG_SHIFT) & FL_SHORT_LEN_FLAG_MASK);
पूर्ण

/**
 * dpaa2_fl_get_len() - Get the length in the FLE
 * @fle: the given frame list entry
 *
 * Return the length field in the frame list entry.
 */
अटल अंतरभूत u32 dpaa2_fl_get_len(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	अगर (dpaa2_fl_लघु_len(fle))
		वापस le32_to_cpu(fle->len) & FL_SHORT_LEN_MASK;

	वापस le32_to_cpu(fle->len);
पूर्ण

/**
 * dpaa2_fl_set_len() - Set the length field of FLE
 * @fle: the given frame list entry
 * @len: the length needs to be set in frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_len(काष्ठा dpaa2_fl_entry *fle, u32 len)
अणु
	fle->len = cpu_to_le32(len);
पूर्ण

/**
 * dpaa2_fl_get_offset() - Get the offset field in the frame list entry
 * @fle: the given frame list entry
 *
 * Return the offset.
 */
अटल अंतरभूत u16 dpaa2_fl_get_offset(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस le16_to_cpu(fle->क्रमmat_offset) & FL_OFFSET_MASK;
पूर्ण

/**
 * dpaa2_fl_set_offset() - Set the offset field of FLE
 * @fle: the given frame list entry
 * @offset: the offset needs to be set in frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_offset(काष्ठा dpaa2_fl_entry *fle, u16 offset)
अणु
	fle->क्रमmat_offset &= cpu_to_le16(~FL_OFFSET_MASK);
	fle->क्रमmat_offset |= cpu_to_le16(offset);
पूर्ण

/**
 * dpaa2_fl_get_क्रमmat() - Get the क्रमmat field in the FLE
 * @fle: the given frame list entry
 *
 * Return the क्रमmat.
 */
अटल अंतरभूत क्रमागत dpaa2_fl_क्रमmat dpaa2_fl_get_क्रमmat(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस (क्रमागत dpaa2_fl_क्रमmat)((le16_to_cpu(fle->क्रमmat_offset) >>
				       FL_FORMAT_SHIFT) & FL_FORMAT_MASK);
पूर्ण

/**
 * dpaa2_fl_set_क्रमmat() - Set the क्रमmat field of FLE
 * @fle: the given frame list entry
 * @क्रमmat: the क्रमmat needs to be set in frame list entry
 */
अटल अंतरभूत व्योम dpaa2_fl_set_क्रमmat(काष्ठा dpaa2_fl_entry *fle,
				       क्रमागत dpaa2_fl_क्रमmat क्रमmat)
अणु
	fle->क्रमmat_offset &= cpu_to_le16(~(FL_FORMAT_MASK << FL_FORMAT_SHIFT));
	fle->क्रमmat_offset |= cpu_to_le16(क्रमmat << FL_FORMAT_SHIFT);
पूर्ण

/**
 * dpaa2_fl_get_bpid() - Get the bpid field in the FLE
 * @fle: the given frame list entry
 *
 * Return the buffer pool id.
 */
अटल अंतरभूत u16 dpaa2_fl_get_bpid(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस le16_to_cpu(fle->bpid) & FL_BPID_MASK;
पूर्ण

/**
 * dpaa2_fl_set_bpid() - Set the bpid field of FLE
 * @fle: the given frame list entry
 * @bpid: buffer pool id to be set
 */
अटल अंतरभूत व्योम dpaa2_fl_set_bpid(काष्ठा dpaa2_fl_entry *fle, u16 bpid)
अणु
	fle->bpid &= cpu_to_le16(~(FL_BPID_MASK));
	fle->bpid |= cpu_to_le16(bpid);
पूर्ण

/**
 * dpaa2_fl_is_final() - Check final bit in FLE
 * @fle: the given frame list entry
 *
 * Return bool.
 */
अटल अंतरभूत bool dpaa2_fl_is_final(स्थिर काष्ठा dpaa2_fl_entry *fle)
अणु
	वापस !!(le16_to_cpu(fle->क्रमmat_offset) >> FL_FINAL_FLAG_SHIFT);
पूर्ण

/**
 * dpaa2_fl_set_final() - Set the final bit in FLE
 * @fle: the given frame list entry
 * @final: the final boolean to be set
 */
अटल अंतरभूत व्योम dpaa2_fl_set_final(काष्ठा dpaa2_fl_entry *fle, bool final)
अणु
	fle->क्रमmat_offset &= cpu_to_le16((~(FL_FINAL_FLAG_MASK <<
					     FL_FINAL_FLAG_SHIFT)) & 0xFFFF);
	fle->क्रमmat_offset |= cpu_to_le16(final << FL_FINAL_FLAG_SHIFT);
पूर्ण

#पूर्ण_अगर /* __FSL_DPAA2_FD_H */
