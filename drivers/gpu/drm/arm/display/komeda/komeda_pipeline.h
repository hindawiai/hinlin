<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _KOMEDA_PIPELINE_H_
#घोषणा _KOMEDA_PIPELINE_H_

#समावेश <linux/types.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश "malidp_utils.h"
#समावेश "komeda_color_mgmt.h"

#घोषणा KOMEDA_MAX_PIPELINES		2
#घोषणा KOMEDA_PIPELINE_MAX_LAYERS	4
#घोषणा KOMEDA_PIPELINE_MAX_SCALERS	2
#घोषणा KOMEDA_COMPONENT_N_INPUTS	5

/* pipeline component IDs */
क्रमागत अणु
	KOMEDA_COMPONENT_LAYER0		= 0,
	KOMEDA_COMPONENT_LAYER1		= 1,
	KOMEDA_COMPONENT_LAYER2		= 2,
	KOMEDA_COMPONENT_LAYER3		= 3,
	KOMEDA_COMPONENT_WB_LAYER	= 7, /* ग_लिखो back layer */
	KOMEDA_COMPONENT_SCALER0	= 8,
	KOMEDA_COMPONENT_SCALER1	= 9,
	KOMEDA_COMPONENT_SPLITTER	= 12,
	KOMEDA_COMPONENT_MERGER		= 14,
	KOMEDA_COMPONENT_COMPIZ0	= 16, /* compositor */
	KOMEDA_COMPONENT_COMPIZ1	= 17,
	KOMEDA_COMPONENT_IPS0		= 20, /* post image processor */
	KOMEDA_COMPONENT_IPS1		= 21,
	KOMEDA_COMPONENT_TIMING_CTRLR	= 22, /* timing controller */
पूर्ण;

#घोषणा KOMEDA_PIPELINE_LAYERS		(BIT(KOMEDA_COMPONENT_LAYER0) |\
					 BIT(KOMEDA_COMPONENT_LAYER1) |\
					 BIT(KOMEDA_COMPONENT_LAYER2) |\
					 BIT(KOMEDA_COMPONENT_LAYER3))

#घोषणा KOMEDA_PIPELINE_SCALERS		(BIT(KOMEDA_COMPONENT_SCALER0) |\
					 BIT(KOMEDA_COMPONENT_SCALER1))

#घोषणा KOMEDA_PIPELINE_COMPIZS		(BIT(KOMEDA_COMPONENT_COMPIZ0) |\
					 BIT(KOMEDA_COMPONENT_COMPIZ1))

#घोषणा KOMEDA_PIPELINE_IMPROCS		(BIT(KOMEDA_COMPONENT_IPS0) |\
					 BIT(KOMEDA_COMPONENT_IPS1))
काष्ठा komeda_component;
काष्ठा komeda_component_state;

/** komeda_component_funcs - component control functions */
काष्ठा komeda_component_funcs अणु
	/** @validate: optional,
	 * component may has special requirements or limitations, this function
	 * supply HW the ability to करो the further HW specअगरic check.
	 */
	पूर्णांक (*validate)(काष्ठा komeda_component *c,
			काष्ठा komeda_component_state *state);
	/** @update: update is a active update */
	व्योम (*update)(काष्ठा komeda_component *c,
		       काष्ठा komeda_component_state *state);
	/** @disable: disable component */
	व्योम (*disable)(काष्ठा komeda_component *c);
	/** @dump_रेजिस्टर: Optional, dump रेजिस्टरs to seq_file */
	व्योम (*dump_रेजिस्टर)(काष्ठा komeda_component *c, काष्ठा seq_file *seq);
पूर्ण;

/**
 * काष्ठा komeda_component
 *
 * काष्ठा komeda_component describe the data flow capabilities क्रम how to link a
 * component पूर्णांकo the display pipeline.
 * all specअगरied components are subclass of this काष्ठाure.
 */
काष्ठा komeda_component अणु
	/** @obj: treat component as निजी obj */
	काष्ठा drm_निजी_obj obj;
	/** @pipeline: the komeda pipeline this component beदीर्घs to */
	काष्ठा komeda_pipeline *pipeline;
	/** @name: component name */
	अक्षर name[32];
	/**
	 * @reg:
	 * component रेजिस्टर base,
	 * which is initialized by chip and used by chip only
	 */
	u32 __iomem *reg;
	/** @id: component id */
	u32 id;
	/**
	 * @hw_id: component hw id,
	 * which is initialized by chip and used by chip only
	 */
	u32 hw_id;

	/**
	 * @max_active_inमाला_दो:
	 * @max_active_outमाला_दो:
	 *
	 * maximum number of inमाला_दो/outमाला_दो that can be active at the same समय
	 * Note:
	 * the number isn't the bit number of @supported_inमाला_दो or
	 * @supported_outमाला_दो, but may be less than it, since component may not
	 * support enabling all @supported_inमाला_दो/outमाला_दो at the same समय.
	 */
	u8 max_active_inमाला_दो;
	/** @max_active_outमाला_दो: maximum number of outमाला_दो */
	u8 max_active_outमाला_दो;
	/**
	 * @supported_inमाला_दो:
	 * @supported_outमाला_दो:
	 *
	 * biपंचांगask of BIT(component->id) क्रम the supported inमाला_दो/outमाला_दो,
	 * describes the possibilities of how a component is linked पूर्णांकo a
	 * pipeline.
	 */
	u32 supported_inमाला_दो;
	/** @supported_outमाला_दो: biपंचांगask of supported output componenet ids */
	u32 supported_outमाला_दो;

	/**
	 * @funcs: chip functions to access HW
	 */
	स्थिर काष्ठा komeda_component_funcs *funcs;
पूर्ण;

/**
 * काष्ठा komeda_component_output
 *
 * a component has multiple outमाला_दो, अगर want to know where the data
 * comes from, only know the component is not enough, we still need to know
 * its output port
 */
काष्ठा komeda_component_output अणु
	/** @component: indicate which component the data comes from */
	काष्ठा komeda_component *component;
	/**
	 * @output_port:
	 * the output port of the &komeda_component_output.component
	 */
	u8 output_port;
पूर्ण;

/**
 * काष्ठा komeda_component_state
 *
 * component_state is the data flow configuration of the component, and it's
 * the superclass of all specअगरic component_state like @komeda_layer_state,
 * @komeda_scaler_state
 */
काष्ठा komeda_component_state अणु
	/** @obj: tracking component_state by drm_atomic_state */
	काष्ठा drm_निजी_state obj;
	/** @component: backpoपूर्णांकer to the component */
	काष्ठा komeda_component *component;
	/**
	 * @binding_user:
	 * currently bound user, the user can be @crtc, @plane or @wb_conn,
	 * which is valid decided by @component and @inमाला_दो
	 *
	 * -  Layer: its user always is plane.
	 * -  compiz/improc/timing_ctrlr: the user is crtc.
	 * -  wb_layer: wb_conn;
	 * -  scaler: plane when input is layer, wb_conn अगर input is compiz.
	 */
	जोड़ अणु
		/** @crtc: backpoपूर्णांकer क्रम user crtc */
		काष्ठा drm_crtc *crtc;
		/** @plane: backpoपूर्णांकer क्रम user plane */
		काष्ठा drm_plane *plane;
		/** @wb_conn: backpoपूर्णांकer क्रम user wb_connector  */
		काष्ठा drm_connector *wb_conn;
		व्योम *binding_user;
	पूर्ण;

	/**
	 * @active_inमाला_दो:
	 *
	 * active_inमाला_दो is biपंचांगask of @inमाला_दो index
	 *
	 * -  active_inमाला_दो = changed_active_inमाला_दो | unchanged_active_inमाला_दो
	 * -  affected_inमाला_दो = old->active_inमाला_दो | new->active_inमाला_दो;
	 * -  disabling_inमाला_दो = affected_inमाला_दो ^ active_inमाला_दो;
	 * -  changed_inमाला_दो = disabling_inमाला_दो | changed_active_inमाला_दो;
	 *
	 * NOTE:
	 * changed_inमाला_दो करोesn't include all active_input but only
	 * @changed_active_inमाला_दो, and this biपंचांगask can be used in chip
	 * level क्रम dirty update.
	 */
	u16 active_inमाला_दो;
	/** @changed_active_inमाला_दो: biपंचांगask of the changed @active_inमाला_दो */
	u16 changed_active_inमाला_दो;
	/** @affected_inमाला_दो: biपंचांगask क्रम affected @inमाला_दो */
	u16 affected_inमाला_दो;
	/**
	 * @inमाला_दो:
	 *
	 * the specअगरic inमाला_दो[i] only valid on BIT(i) has been set in
	 * @active_inमाला_दो, अगर not the inमाला_दो[i] is undefined.
	 */
	काष्ठा komeda_component_output inमाला_दो[KOMEDA_COMPONENT_N_INPUTS];
पूर्ण;

अटल अंतरभूत u16 component_disabling_inमाला_दो(काष्ठा komeda_component_state *st)
अणु
	वापस st->affected_inमाला_दो ^ st->active_inमाला_दो;
पूर्ण

अटल अंतरभूत u16 component_changed_inमाला_दो(काष्ठा komeda_component_state *st)
अणु
	वापस component_disabling_inमाला_दो(st) | st->changed_active_inमाला_दो;
पूर्ण

#घोषणा क्रम_each_changed_input(st, i)	\
	क्रम ((i) = 0; (i) < (st)->component->max_active_inमाला_दो; (i)++)	\
		अगर (has_bit((i), component_changed_inमाला_दो(st)))

#घोषणा to_comp(__c)	(((__c) == शून्य) ? शून्य : &((__c)->base))
#घोषणा to_cpos(__c)	((काष्ठा komeda_component **)&(__c))

काष्ठा komeda_layer अणु
	काष्ठा komeda_component base;
	/* accepted h/v input range beक्रमe rotation */
	काष्ठा malidp_range hsize_in, vsize_in;
	u32 layer_type; /* RICH, SIMPLE or WB */
	u32 line_sz;
	u32 yuv_line_sz; /* maximum line size क्रम YUV422 and YUV420 */
	u32 supported_rots;
	/* komeda supports layer split which splits a whole image to two parts
	 * left and right and handle them by two inभागidual layer processors
	 * Note: left/right are always according to the final display rect,
	 * not the source buffer.
	 */
	काष्ठा komeda_layer *right;
पूर्ण;

काष्ठा komeda_layer_state अणु
	काष्ठा komeda_component_state base;
	/* layer specअगरic configuration state */
	u16 hsize, vsize;
	u32 rot;
	u16 afbc_crop_l;
	u16 afbc_crop_r;
	u16 afbc_crop_t;
	u16 afbc_crop_b;
	dma_addr_t addr[3];
पूर्ण;

काष्ठा komeda_scaler अणु
	काष्ठा komeda_component base;
	काष्ठा malidp_range hsize, vsize;
	u32 max_upscaling;
	u32 max_करोwnscaling;
	u8 scaling_split_overlap; /* split overlap क्रम scaling */
	u8 enh_split_overlap; /* split overlap क्रम image enhancement */
पूर्ण;

काष्ठा komeda_scaler_state अणु
	काष्ठा komeda_component_state base;
	u16 hsize_in, vsize_in;
	u16 hsize_out, vsize_out;
	u16 total_hsize_in, total_vsize_in;
	u16 total_hsize_out; /* total_xxxx are size beक्रमe split */
	u16 left_crop, right_crop;
	u8 en_scaling : 1,
	   en_alpha : 1, /* enable alpha processing */
	   en_img_enhancement : 1,
	   en_split : 1,
	   right_part : 1; /* right part of split image */
पूर्ण;

काष्ठा komeda_compiz अणु
	काष्ठा komeda_component base;
	काष्ठा malidp_range hsize, vsize;
पूर्ण;

काष्ठा komeda_compiz_input_cfg अणु
	u16 hsize, vsize;
	u16 hoffset, voffset;
	u8 pixel_blend_mode, layer_alpha;
पूर्ण;

काष्ठा komeda_compiz_state अणु
	काष्ठा komeda_component_state base;
	/* composition size */
	u16 hsize, vsize;
	काष्ठा komeda_compiz_input_cfg cins[KOMEDA_COMPONENT_N_INPUTS];
पूर्ण;

काष्ठा komeda_merger अणु
	काष्ठा komeda_component base;
	काष्ठा malidp_range hsize_merged;
	काष्ठा malidp_range vsize_merged;
पूर्ण;

काष्ठा komeda_merger_state अणु
	काष्ठा komeda_component_state base;
	u16 hsize_merged;
	u16 vsize_merged;
पूर्ण;

काष्ठा komeda_splitter अणु
	काष्ठा komeda_component base;
	काष्ठा malidp_range hsize, vsize;
पूर्ण;

काष्ठा komeda_splitter_state अणु
	काष्ठा komeda_component_state base;
	u16 hsize, vsize;
	u16 overlap;
पूर्ण;

काष्ठा komeda_improc अणु
	काष्ठा komeda_component base;
	u32 supported_color_क्रमmats;  /* DRM_RGB/YUV444/YUV420*/
	u32 supported_color_depths; /* BIT(8) | BIT(10)*/
	u8 supports_degamma : 1;
	u8 supports_csc : 1;
	u8 supports_gamma : 1;
पूर्ण;

काष्ठा komeda_improc_state अणु
	काष्ठा komeda_component_state base;
	u8 color_क्रमmat, color_depth;
	u16 hsize, vsize;
	u32 fgamma_coeffs[KOMEDA_N_GAMMA_COEFFS];
	u32 cपंचांग_coeffs[KOMEDA_N_CTM_COEFFS];
पूर्ण;

/* display timing controller */
काष्ठा komeda_timing_ctrlr अणु
	काष्ठा komeda_component base;
	u8 supports_dual_link : 1;
पूर्ण;

काष्ठा komeda_timing_ctrlr_state अणु
	काष्ठा komeda_component_state base;
पूर्ण;

/* Why define A separated काष्ठाure but not use plane_state directly ?
 * 1. Komeda supports layer_split which means a plane_state can be split and
 *    handled by two layers, one layer only handle half of plane image.
 * 2. Fix up the user properties according to HW's capabilities, like user
 *    set rotation to R180, but HW only supports REFLECT_X+Y. the rot here is
 *    after drm_rotation_simplअगरy()
 */
काष्ठा komeda_data_flow_cfg अणु
	काष्ठा komeda_component_output input;
	u16 in_x, in_y, in_w, in_h;
	u32 out_x, out_y, out_w, out_h;
	u16 total_in_h, total_in_w;
	u16 total_out_w;
	u16 left_crop, right_crop, overlap;
	u32 rot;
	पूर्णांक blending_zorder;
	u8 pixel_blend_mode, layer_alpha;
	u8 en_scaling : 1,
	   en_img_enhancement : 1,
	   en_split : 1,
	   is_yuv : 1,
	   right_part : 1; /* right part of display image अगर split enabled */
पूर्ण;

काष्ठा komeda_pipeline_funcs अणु
	/* check अगर the aclk (मुख्य engine घड़ी) can satisfy the घड़ी
	 * requirements of the करोwnscaling that specअगरied by dflow
	 */
	पूर्णांक (*करोwnscaling_clk_check)(काष्ठा komeda_pipeline *pipe,
				     काष्ठा drm_display_mode *mode,
				     अचिन्हित दीर्घ aclk_rate,
				     काष्ठा komeda_data_flow_cfg *dflow);
	/* dump_रेजिस्टर: Optional, dump रेजिस्टरs to seq_file */
	व्योम (*dump_रेजिस्टर)(काष्ठा komeda_pipeline *pipe,
			      काष्ठा seq_file *sf);
पूर्ण;

/**
 * काष्ठा komeda_pipeline
 *
 * Represent a complete display pipeline and hold all functional components.
 */
काष्ठा komeda_pipeline अणु
	/** @obj: link pipeline as निजी obj of drm_atomic_state */
	काष्ठा drm_निजी_obj obj;
	/** @mdev: the parent komeda_dev */
	काष्ठा komeda_dev *mdev;
	/** @pxlclk: pixel घड़ी */
	काष्ठा clk *pxlclk;
	/** @id: pipeline id */
	पूर्णांक id;
	/** @avail_comps: available components mask of pipeline */
	u32 avail_comps;
	/**
	 * @standalone_disabled_comps:
	 *
	 * When disable the pipeline, some components can not be disabled
	 * together with others, but need a sparated and standalone disable.
	 * The standalone_disabled_comps are the components which need to be
	 * disabled standalone, and this concept also पूर्णांकroduce concept of
	 * two phase.
	 * phase 1: क्रम disabling the common components.
	 * phase 2: क्रम disabling the standaदीर्घ_disabled_comps.
	 */
	u32 standalone_disabled_comps;
	/** @n_layers: the number of layer on @layers */
	पूर्णांक n_layers;
	/** @layers: the pipeline layers */
	काष्ठा komeda_layer *layers[KOMEDA_PIPELINE_MAX_LAYERS];
	/** @n_scalers: the number of scaler on @scalers */
	पूर्णांक n_scalers;
	/** @scalers: the pipeline scalers */
	काष्ठा komeda_scaler *scalers[KOMEDA_PIPELINE_MAX_SCALERS];
	/** @compiz: compositor */
	काष्ठा komeda_compiz *compiz;
	/** @splitter: क्रम split the compiz output to two half data flows */
	काष्ठा komeda_splitter *splitter;
	/** @merger: merger */
	काष्ठा komeda_merger *merger;
	/** @wb_layer: ग_लिखोback layer */
	काष्ठा komeda_layer  *wb_layer;
	/** @improc: post image processor */
	काष्ठा komeda_improc *improc;
	/** @ctrlr: timing controller */
	काष्ठा komeda_timing_ctrlr *ctrlr;
	/** @funcs: chip निजी pipeline functions */
	स्थिर काष्ठा komeda_pipeline_funcs *funcs;

	/** @of_node: pipeline dt node */
	काष्ठा device_node *of_node;
	/** @of_output_port: pipeline output port */
	काष्ठा device_node *of_output_port;
	/** @of_output_links: output connector device nodes */
	काष्ठा device_node *of_output_links[2];
	/** @dual_link: true अगर of_output_links[0] and [1] are both valid */
	bool dual_link;
पूर्ण;

/**
 * काष्ठा komeda_pipeline_state
 *
 * NOTE:
 * Unlike the pipeline, pipeline_state करोesnै t gather any component_state
 * पूर्णांकo it. It because all component will be managed by drm_atomic_state.
 */
काष्ठा komeda_pipeline_state अणु
	/** @obj: tracking pipeline_state by drm_atomic_state */
	काष्ठा drm_निजी_state obj;
	/** @pipe: backpoपूर्णांकer to the pipeline */
	काष्ठा komeda_pipeline *pipe;
	/** @crtc: currently bound crtc */
	काष्ठा drm_crtc *crtc;
	/**
	 * @active_comps:
	 *
	 * biपंचांगask - BIT(component->id) of active components
	 */
	u32 active_comps;
पूर्ण;

#घोषणा to_layer(c)	container_of(c, काष्ठा komeda_layer, base)
#घोषणा to_compiz(c)	container_of(c, काष्ठा komeda_compiz, base)
#घोषणा to_scaler(c)	container_of(c, काष्ठा komeda_scaler, base)
#घोषणा to_splitter(c)	container_of(c, काष्ठा komeda_splitter, base)
#घोषणा to_merger(c)	container_of(c, काष्ठा komeda_merger, base)
#घोषणा to_improc(c)	container_of(c, काष्ठा komeda_improc, base)
#घोषणा to_ctrlr(c)	container_of(c, काष्ठा komeda_timing_ctrlr, base)

#घोषणा to_layer_st(c)	container_of(c, काष्ठा komeda_layer_state, base)
#घोषणा to_compiz_st(c)	container_of(c, काष्ठा komeda_compiz_state, base)
#घोषणा to_scaler_st(c)	container_of(c, काष्ठा komeda_scaler_state, base)
#घोषणा to_splitter_st(c) container_of(c, काष्ठा komeda_splitter_state, base)
#घोषणा to_merger_st(c)	container_of(c, काष्ठा komeda_merger_state, base)
#घोषणा to_improc_st(c)	container_of(c, काष्ठा komeda_improc_state, base)
#घोषणा to_ctrlr_st(c)	container_of(c, काष्ठा komeda_timing_ctrlr_state, base)

#घोषणा priv_to_comp_st(o) container_of(o, काष्ठा komeda_component_state, obj)
#घोषणा priv_to_pipe_st(o) container_of(o, काष्ठा komeda_pipeline_state, obj)

/* pipeline APIs */
काष्ठा komeda_pipeline *
komeda_pipeline_add(काष्ठा komeda_dev *mdev, माप_प्रकार size,
		    स्थिर काष्ठा komeda_pipeline_funcs *funcs);
व्योम komeda_pipeline_destroy(काष्ठा komeda_dev *mdev,
			     काष्ठा komeda_pipeline *pipe);
काष्ठा komeda_pipeline *
komeda_pipeline_get_slave(काष्ठा komeda_pipeline *master);
पूर्णांक komeda_assemble_pipelines(काष्ठा komeda_dev *mdev);
काष्ठा komeda_component *
komeda_pipeline_get_component(काष्ठा komeda_pipeline *pipe, पूर्णांक id);
काष्ठा komeda_component *
komeda_pipeline_get_first_component(काष्ठा komeda_pipeline *pipe,
				    u32 comp_mask);

व्योम komeda_pipeline_dump_रेजिस्टर(काष्ठा komeda_pipeline *pipe,
				   काष्ठा seq_file *sf);

/* component APIs */
बाह्य __म_लिखो(10, 11)
काष्ठा komeda_component *
komeda_component_add(काष्ठा komeda_pipeline *pipe,
		     माप_प्रकार comp_sz, u32 id, u32 hw_id,
		     स्थिर काष्ठा komeda_component_funcs *funcs,
		     u8 max_active_inमाला_दो, u32 supported_inमाला_दो,
		     u8 max_active_outमाला_दो, u32 __iomem *reg,
		     स्थिर अक्षर *name_fmt, ...);

व्योम komeda_component_destroy(काष्ठा komeda_dev *mdev,
			      काष्ठा komeda_component *c);

अटल अंतरभूत काष्ठा komeda_component *
komeda_component_pickup_output(काष्ठा komeda_component *c, u32 avail_comps)
अणु
	u32 avail_inमाला_दो = c->supported_outमाला_दो & (avail_comps);

	वापस komeda_pipeline_get_first_component(c->pipeline, avail_inमाला_दो);
पूर्ण

काष्ठा komeda_plane_state;
काष्ठा komeda_crtc_state;
काष्ठा komeda_crtc;

व्योम pipeline_composition_size(काष्ठा komeda_crtc_state *kcrtc_st,
			       u16 *hsize, u16 *vsize);

पूर्णांक komeda_build_layer_data_flow(काष्ठा komeda_layer *layer,
				 काष्ठा komeda_plane_state *kplane_st,
				 काष्ठा komeda_crtc_state *kcrtc_st,
				 काष्ठा komeda_data_flow_cfg *dflow);
पूर्णांक komeda_build_wb_data_flow(काष्ठा komeda_layer *wb_layer,
			      काष्ठा drm_connector_state *conn_st,
			      काष्ठा komeda_crtc_state *kcrtc_st,
			      काष्ठा komeda_data_flow_cfg *dflow);
पूर्णांक komeda_build_display_data_flow(काष्ठा komeda_crtc *kcrtc,
				   काष्ठा komeda_crtc_state *kcrtc_st);

पूर्णांक komeda_build_layer_split_data_flow(काष्ठा komeda_layer *left,
				       काष्ठा komeda_plane_state *kplane_st,
				       काष्ठा komeda_crtc_state *kcrtc_st,
				       काष्ठा komeda_data_flow_cfg *dflow);
पूर्णांक komeda_build_wb_split_data_flow(काष्ठा komeda_layer *wb_layer,
				    काष्ठा drm_connector_state *conn_st,
				    काष्ठा komeda_crtc_state *kcrtc_st,
				    काष्ठा komeda_data_flow_cfg *dflow);

पूर्णांक komeda_release_unclaimed_resources(काष्ठा komeda_pipeline *pipe,
				       काष्ठा komeda_crtc_state *kcrtc_st);

काष्ठा komeda_pipeline_state *
komeda_pipeline_get_old_state(काष्ठा komeda_pipeline *pipe,
			      काष्ठा drm_atomic_state *state);
bool komeda_pipeline_disable(काष्ठा komeda_pipeline *pipe,
			     काष्ठा drm_atomic_state *old_state);
व्योम komeda_pipeline_update(काष्ठा komeda_pipeline *pipe,
			    काष्ठा drm_atomic_state *old_state);

व्योम komeda_complete_data_flow_cfg(काष्ठा komeda_layer *layer,
				   काष्ठा komeda_data_flow_cfg *dflow,
				   काष्ठा drm_framebuffer *fb);

#पूर्ण_अगर /* _KOMEDA_PIPELINE_H_*/
