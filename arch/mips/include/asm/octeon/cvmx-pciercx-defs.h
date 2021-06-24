<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

#अगर_अघोषित __CVMX_PCIERCX_DEFS_H__
#घोषणा __CVMX_PCIERCX_DEFS_H__

#समावेश <uapi/यंत्र/bitfield.h>

#घोषणा CVMX_PCIERCX_CFG001(block_id) (0x0000000000000004ull)
#घोषणा CVMX_PCIERCX_CFG006(block_id) (0x0000000000000018ull)
#घोषणा CVMX_PCIERCX_CFG008(block_id) (0x0000000000000020ull)
#घोषणा CVMX_PCIERCX_CFG009(block_id) (0x0000000000000024ull)
#घोषणा CVMX_PCIERCX_CFG010(block_id) (0x0000000000000028ull)
#घोषणा CVMX_PCIERCX_CFG011(block_id) (0x000000000000002Cull)
#घोषणा CVMX_PCIERCX_CFG030(block_id) (0x0000000000000078ull)
#घोषणा CVMX_PCIERCX_CFG031(block_id) (0x000000000000007Cull)
#घोषणा CVMX_PCIERCX_CFG032(block_id) (0x0000000000000080ull)
#घोषणा CVMX_PCIERCX_CFG034(block_id) (0x0000000000000088ull)
#घोषणा CVMX_PCIERCX_CFG035(block_id) (0x000000000000008Cull)
#घोषणा CVMX_PCIERCX_CFG040(block_id) (0x00000000000000A0ull)
#घोषणा CVMX_PCIERCX_CFG066(block_id) (0x0000000000000108ull)
#घोषणा CVMX_PCIERCX_CFG069(block_id) (0x0000000000000114ull)
#घोषणा CVMX_PCIERCX_CFG070(block_id) (0x0000000000000118ull)
#घोषणा CVMX_PCIERCX_CFG075(block_id) (0x000000000000012Cull)
#घोषणा CVMX_PCIERCX_CFG448(block_id) (0x0000000000000700ull)
#घोषणा CVMX_PCIERCX_CFG452(block_id) (0x0000000000000710ull)
#घोषणा CVMX_PCIERCX_CFG455(block_id) (0x000000000000071Cull)
#घोषणा CVMX_PCIERCX_CFG515(block_id) (0x000000000000080Cull)

जोड़ cvmx_pciercx_cfg001 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg001_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t dpe:1,
		__BITFIELD_FIELD(uपूर्णांक32_t sse:1,
		__BITFIELD_FIELD(uपूर्णांक32_t rma:1,
		__BITFIELD_FIELD(uपूर्णांक32_t rta:1,
		__BITFIELD_FIELD(uपूर्णांक32_t sta:1,
		__BITFIELD_FIELD(uपूर्णांक32_t devt:2,
		__BITFIELD_FIELD(uपूर्णांक32_t mdpe:1,
		__BITFIELD_FIELD(uपूर्णांक32_t fbb:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_22_22:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m66:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cl:1,
		__BITFIELD_FIELD(uपूर्णांक32_t i_stat:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_11_18:8,
		__BITFIELD_FIELD(uपूर्णांक32_t i_dis:1,
		__BITFIELD_FIELD(uपूर्णांक32_t fbbe:1,
		__BITFIELD_FIELD(uपूर्णांक32_t see:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ids_wcc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t per:1,
		__BITFIELD_FIELD(uपूर्णांक32_t vps:1,
		__BITFIELD_FIELD(uपूर्णांक32_t mwice:1,
		__BITFIELD_FIELD(uपूर्णांक32_t scse:1,
		__BITFIELD_FIELD(uपूर्णांक32_t me:1,
		__BITFIELD_FIELD(uपूर्णांक32_t msae:1,
		__BITFIELD_FIELD(uपूर्णांक32_t isae:1,
		;))))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg006 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg006_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t slt:8,
		__BITFIELD_FIELD(uपूर्णांक32_t subbnum:8,
		__BITFIELD_FIELD(uपूर्णांक32_t sbnum:8,
		__BITFIELD_FIELD(uपूर्णांक32_t pbnum:8,
		;))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg008 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg008_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t ml_addr:12,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_16_19:4,
		__BITFIELD_FIELD(uपूर्णांक32_t mb_addr:12,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_0_3:4,
		;))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg009 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg009_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t lmem_limit:12,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_17_19:3,
		__BITFIELD_FIELD(uपूर्णांक32_t mem64b:1,
		__BITFIELD_FIELD(uपूर्णांक32_t lmem_base:12,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_1_3:3,
		__BITFIELD_FIELD(uपूर्णांक32_t mem64a:1,
		;))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg010 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg010_s अणु
		uपूर्णांक32_t umem_base;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg011 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg011_s अणु
		uपूर्णांक32_t umem_limit;
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg030 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg030_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_22_31:10,
		__BITFIELD_FIELD(uपूर्णांक32_t tp:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ap_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ur_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t fe_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t nfe_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ce_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_15_15:1,
		__BITFIELD_FIELD(uपूर्णांक32_t mrrs:3,
		__BITFIELD_FIELD(uपूर्णांक32_t ns_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ap_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pf_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t etf_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t mps:3,
		__BITFIELD_FIELD(uपूर्णांक32_t ro_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ur_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t fe_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t nfe_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ce_en:1,
		;)))))))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg031 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg031_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t pnum:8,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_23_23:1,
		__BITFIELD_FIELD(uपूर्णांक32_t aspm:1,
		__BITFIELD_FIELD(uपूर्णांक32_t lbnc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t dllarc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t sderc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cpm:1,
		__BITFIELD_FIELD(uपूर्णांक32_t l1el:3,
		__BITFIELD_FIELD(uपूर्णांक32_t l0el:3,
		__BITFIELD_FIELD(uपूर्णांक32_t aslpms:2,
		__BITFIELD_FIELD(uपूर्णांक32_t mlw:6,
		__BITFIELD_FIELD(uपूर्णांक32_t mls:4,
		;))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg032 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg032_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t lab:1,
		__BITFIELD_FIELD(uपूर्णांक32_t lbm:1,
		__BITFIELD_FIELD(uपूर्णांक32_t dlla:1,
		__BITFIELD_FIELD(uपूर्णांक32_t scc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t lt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_26_26:1,
		__BITFIELD_FIELD(uपूर्णांक32_t nlw:6,
		__BITFIELD_FIELD(uपूर्णांक32_t ls:4,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_12_15:4,
		__BITFIELD_FIELD(uपूर्णांक32_t lab_पूर्णांक_enb:1,
		__BITFIELD_FIELD(uपूर्णांक32_t lbm_पूर्णांक_enb:1,
		__BITFIELD_FIELD(uपूर्णांक32_t hawd:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ecpm:1,
		__BITFIELD_FIELD(uपूर्णांक32_t es:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ccc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t rl:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ld:1,
		__BITFIELD_FIELD(uपूर्णांक32_t rcb:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_2_2:1,
		__BITFIELD_FIELD(uपूर्णांक32_t aslpc:2,
		;))))))))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg034 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg034_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_25_31:7,
		__BITFIELD_FIELD(uपूर्णांक32_t dlls_c:1,
		__BITFIELD_FIELD(uपूर्णांक32_t emis:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pds:1,
		__BITFIELD_FIELD(uपूर्णांक32_t mrlss:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ccपूर्णांक_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pd_c:1,
		__BITFIELD_FIELD(uपूर्णांक32_t mrls_c:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pf_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t abp_d:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_13_15:3,
		__BITFIELD_FIELD(uपूर्णांक32_t dlls_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t emic:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pcc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pic:1,
		__BITFIELD_FIELD(uपूर्णांक32_t aic:1,
		__BITFIELD_FIELD(uपूर्णांक32_t hpपूर्णांक_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ccपूर्णांक_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pd_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t mrls_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pf_en:1,
		__BITFIELD_FIELD(uपूर्णांक32_t abp_en:1,
		;))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg035 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg035_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_17_31:15,
		__BITFIELD_FIELD(uपूर्णांक32_t crssv:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_5_15:11,
		__BITFIELD_FIELD(uपूर्णांक32_t crssve:1,
		__BITFIELD_FIELD(uपूर्णांक32_t pmeie:1,
		__BITFIELD_FIELD(uपूर्णांक32_t sefee:1,
		__BITFIELD_FIELD(uपूर्णांक32_t senfee:1,
		__BITFIELD_FIELD(uपूर्णांक32_t secee:1,
		;))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg040 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg040_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_22_31:10,
		__BITFIELD_FIELD(uपूर्णांक32_t ler:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ep3s:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ep2s:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ep1s:1,
		__BITFIELD_FIELD(uपूर्णांक32_t eqc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cdl:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cde:4,
		__BITFIELD_FIELD(uपूर्णांक32_t csos:1,
		__BITFIELD_FIELD(uपूर्णांक32_t emc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t पंचांग:3,
		__BITFIELD_FIELD(uपूर्णांक32_t sde:1,
		__BITFIELD_FIELD(uपूर्णांक32_t hasd:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ec:1,
		__BITFIELD_FIELD(uपूर्णांक32_t tls:4,
		;)))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg070 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg070_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_12_31:20,
		__BITFIELD_FIELD(uपूर्णांक32_t tplp:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_9_10:2,
		__BITFIELD_FIELD(uपूर्णांक32_t ce:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ge:1,
		__BITFIELD_FIELD(uपूर्णांक32_t gc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t fep:5,
		;))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg075 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg075_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_3_31:29,
		__BITFIELD_FIELD(uपूर्णांक32_t fere:1,
		__BITFIELD_FIELD(uपूर्णांक32_t nfere:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cere:1,
		;))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg448 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg448_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t rtl:16,
		__BITFIELD_FIELD(uपूर्णांक32_t rtltl:16,
		;))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg452 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg452_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_26_31:6,
		__BITFIELD_FIELD(uपूर्णांक32_t eccrc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_22_24:3,
		__BITFIELD_FIELD(uपूर्णांक32_t lme:6,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_12_15:4,
		__BITFIELD_FIELD(uपूर्णांक32_t link_rate:4,
		__BITFIELD_FIELD(uपूर्णांक32_t flm:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_6_6:1,
		__BITFIELD_FIELD(uपूर्णांक32_t dllle:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_4_4:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ra:1,
		__BITFIELD_FIELD(uपूर्णांक32_t le:1,
		__BITFIELD_FIELD(uपूर्णांक32_t sd:1,
		__BITFIELD_FIELD(uपूर्णांक32_t omr:1,
		;))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg455 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg455_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t m_cfg0_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_io_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t msg_ctrl:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_ecrc_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_ecrc_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_len_err:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_attr_err:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_tc_err:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_fun_err:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_rid_err:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cpl_tag_err:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_lk_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_cfg1_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_bar_match:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_pois_filt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t m_fun:1,
		__BITFIELD_FIELD(uपूर्णांक32_t dfcwt:1,
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_11_14:4,
		__BITFIELD_FIELD(uपूर्णांक32_t skpiv:11,
		;)))))))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pciercx_cfg515 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pciercx_cfg515_s अणु
		__BITFIELD_FIELD(uपूर्णांक32_t reserved_21_31:11,
		__BITFIELD_FIELD(uपूर्णांक32_t s_d_e:1,
		__BITFIELD_FIELD(uपूर्णांक32_t ctcrb:1,
		__BITFIELD_FIELD(uपूर्णांक32_t cpyts:1,
		__BITFIELD_FIELD(uपूर्णांक32_t dsc:1,
		__BITFIELD_FIELD(uपूर्णांक32_t le:9,
		__BITFIELD_FIELD(uपूर्णांक32_t n_fts:8,
		;)))))))
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
