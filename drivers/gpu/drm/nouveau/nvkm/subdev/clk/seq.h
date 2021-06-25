<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_CLK_SEQ_H__
#घोषणा __NVKM_CLK_SEQ_H__
#समावेश <subdev/bus/hwsq.h>

#घोषणा clk_init(s,p)       hwsq_init(&(s)->base, (p))
#घोषणा clk_exec(s,e)       hwsq_exec(&(s)->base, (e))
#घोषणा clk_have(s,r)       ((s)->r_##r.addr != 0x000000)
#घोषणा clk_rd32(s,r)       hwsq_rd32(&(s)->base, &(s)->r_##r)
#घोषणा clk_wr32(s,r,d)     hwsq_wr32(&(s)->base, &(s)->r_##r, (d))
#घोषणा clk_mask(s,r,m,d)   hwsq_mask(&(s)->base, &(s)->r_##r, (m), (d))
#घोषणा clk_setf(s,f,d)     hwsq_setf(&(s)->base, (f), (d))
#घोषणा clk_रुको(s,f,d)     hwsq_रुको(&(s)->base, (f), (d))
#घोषणा clk_nsec(s,n)       hwsq_nsec(&(s)->base, (n))
#पूर्ण_अगर
