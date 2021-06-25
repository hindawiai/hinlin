<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CL5070_H__
#घोषणा __NVIF_CL5070_H__

#घोषणा NV50_DISP_MTHD                                                     0x00

काष्ठा nv50_disp_mthd_v0 अणु
	__u8  version;
#घोषणा NV50_DISP_SCANOUTPOS                                               0x00
	__u8  method;
	__u8  head;
	__u8  pad03[5];
पूर्ण;

काष्ठा nv50_disp_scanoutpos_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__s64 समय[2];
	__u16 vblanks;
	__u16 vblanke;
	__u16 vtotal;
	__u16 vline;
	__u16 hblanks;
	__u16 hblanke;
	__u16 htotal;
	__u16 hline;
पूर्ण;

काष्ठा nv50_disp_mthd_v1 अणु
	__u8  version;
#घोषणा NV50_DISP_MTHD_V1_ACQUIRE                                          0x01
#घोषणा NV50_DISP_MTHD_V1_RELEASE                                          0x02
#घोषणा NV50_DISP_MTHD_V1_DAC_LOAD                                         0x11
#घोषणा NV50_DISP_MTHD_V1_SOR_HDA_ELD                                      0x21
#घोषणा NV50_DISP_MTHD_V1_SOR_HDMI_PWR                                     0x22
#घोषणा NV50_DISP_MTHD_V1_SOR_LVDS_SCRIPT                                  0x23
#घोषणा NV50_DISP_MTHD_V1_SOR_DP_MST_LINK                                  0x25
#घोषणा NV50_DISP_MTHD_V1_SOR_DP_MST_VCPI                                  0x26
	__u8  method;
	__u16 hasht;
	__u16 hashm;
	__u8  pad06[2];
पूर्ण;

काष्ठा nv50_disp_acquire_v0 अणु
	__u8  version;
	__u8  or;
	__u8  link;
	__u8  hda;
	__u8  pad04[4];
पूर्ण;

काष्ठा nv50_disp_dac_load_v0 अणु
	__u8  version;
	__u8  load;
	__u8  pad02[2];
	__u32 data;
पूर्ण;

काष्ठा nv50_disp_sor_hda_eld_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__u8  data[];
पूर्ण;

काष्ठा nv50_disp_sor_hdmi_pwr_v0 अणु
	__u8  version;
	__u8  state;
	__u8  max_ac_packet;
	__u8  rekey;
	__u8  avi_infoframe_length;
	__u8  venकरोr_infoframe_length;
#घोषणा NV50_DISP_SOR_HDMI_PWR_V0_SCDC_SCRAMBLE (1 << 0)
#घोषणा NV50_DISP_SOR_HDMI_PWR_V0_SCDC_DIV_BY_4 (1 << 1)
	__u8  scdc;
	__u8  pad07[1];
पूर्ण;

काष्ठा nv50_disp_sor_lvds_script_v0 अणु
	__u8  version;
	__u8  pad01[1];
	__u16 script;
	__u8  pad04[4];
पूर्ण;

काष्ठा nv50_disp_sor_dp_mst_link_v0 अणु
	__u8  version;
	__u8  state;
	__u8  pad02[6];
पूर्ण;

काष्ठा nv50_disp_sor_dp_mst_vcpi_v0 अणु
	__u8  version;
	__u8  pad01[1];
	__u8  start_slot;
	__u8  num_slots;
	__u16 pbn;
	__u16 aligned_pbn;
पूर्ण;
#पूर्ण_अगर
