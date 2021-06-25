<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
काष्ठा regmap;

/**
 * क्रमागत icst_control_type - the type of ICST control रेजिस्टर
 */
क्रमागत icst_control_type अणु
	ICST_VERSATILE, /* The standard type, all control bits available */
	ICST_INTEGRATOR_AP_CM, /* Only 8 bits of VDW available */
	ICST_INTEGRATOR_AP_SYS, /* Only 8 bits of VDW available */
	ICST_INTEGRATOR_AP_PCI, /* Odd bit pattern storage */
	ICST_INTEGRATOR_CP_CM_CORE, /* Only 8 bits of VDW and 3 bits of OD */
	ICST_INTEGRATOR_CP_CM_MEM, /* Only 8 bits of VDW and 3 bits of OD */
	ICST_INTEGRATOR_IM_PD1, /* Like the Versatile, all control bits */
पूर्ण;

/**
 * काष्ठा clk_icst_desc - descriptor क्रम the ICST VCO
 * @params: ICST parameters
 * @vco_offset: offset to the ICST VCO from the provided memory base
 * @lock_offset: offset to the ICST VCO locking रेजिस्टर from the provided
 *	memory base
 */
काष्ठा clk_icst_desc अणु
	स्थिर काष्ठा icst_params *params;
	u32 vco_offset;
	u32 lock_offset;
पूर्ण;

काष्ठा clk *icst_clk_रेजिस्टर(काष्ठा device *dev,
			      स्थिर काष्ठा clk_icst_desc *desc,
			      स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name,
			      व्योम __iomem *base);

काष्ठा clk *icst_clk_setup(काष्ठा device *dev,
			   स्थिर काष्ठा clk_icst_desc *desc,
			   स्थिर अक्षर *name,
			   स्थिर अक्षर *parent_name,
			   काष्ठा regmap *map,
			   क्रमागत icst_control_type ctype);
