<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FBRAM_SEQ_H__
#घोषणा __NVKM_FBRAM_SEQ_H__
#समावेश <subdev/bus/hwsq.h>

#घोषणा ram_init(s,p)       hwsq_init(&(s)->base, (p))
#घोषणा ram_exec(s,e)       hwsq_exec(&(s)->base, (e))
#घोषणा ram_have(s,r)       ((s)->r_##r.addr != 0x000000)
#घोषणा ram_rd32(s,r)       hwsq_rd32(&(s)->base, &(s)->r_##r)
#घोषणा ram_wr32(s,r,d)     hwsq_wr32(&(s)->base, &(s)->r_##r, (d))
#घोषणा ram_nuke(s,r)       hwsq_nuke(&(s)->base, &(s)->r_##r)
#घोषणा ram_mask(s,r,m,d)   hwsq_mask(&(s)->base, &(s)->r_##r, (m), (d))
#घोषणा ram_setf(s,f,d)     hwsq_setf(&(s)->base, (f), (d))
#घोषणा ram_रुको(s,f,d)     hwsq_रुको(&(s)->base, (f), (d))
#घोषणा ram_रुको_vblank(s)  hwsq_रुको_vblank(&(s)->base)
#घोषणा ram_nsec(s,n)       hwsq_nsec(&(s)->base, (n))
#पूर्ण_अगर
