<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CPU_DEVICE_ID
#घोषणा _ASM_X86_CPU_DEVICE_ID

/*
 * Declare drivers beदीर्घing to specअगरic x86 CPUs
 * Similar in spirit to pci_device_id and related PCI functions
 *
 * The wildcard initializers are in mod_devicetable.h because
 * file2alias needs them. Sigh.
 */
#समावेश <linux/mod_devicetable.h>
/* Get the INTEL_FAM* model defines */
#समावेश <यंत्र/पूर्णांकel-family.h>
/* And the X86_VENDOR_* ones */
#समावेश <यंत्र/processor.h>

/* Centaur FAM6 models */
#घोषणा X86_CENTAUR_FAM6_C7_A		0xa
#घोषणा X86_CENTAUR_FAM6_C7_D		0xd
#घोषणा X86_CENTAUR_FAM6_न_अंकO		0xf

#घोषणा X86_STEPPINGS(mins, maxs)    GENMASK(maxs, mins)
/**
 * X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE - Base macro क्रम CPU matching
 * @_venकरोr:	The venकरोr name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@_venकरोr
 * @_family:	The family number or X86_FAMILY_ANY
 * @_model:	The model number, model स्थिरant or X86_MODEL_ANY
 * @_steppings:	Biपंचांगask क्रम steppings, stepping स्थिरant or X86_STEPPING_ANY
 * @_feature:	A X86_FEATURE bit or X86_FEATURE_ANY
 * @_data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * Use only अगर you need all selectors. Otherwise use one of the लघुer
 * macros of the X86_MATCH_* family. If there is no matching लघुhand
 * macro, consider to add one. If you really need to wrap one of the macros
 * पूर्णांकo another macro at the usage site क्रम good reasons, then please
 * start this local macro with X86_MATCH to allow easy grepping.
 */
#घोषणा X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE(_venकरोr, _family, _model, \
						    _steppings, _feature, _data) अणु \
	.venकरोr		= X86_VENDOR_##_venकरोr,				\
	.family		= _family,					\
	.model		= _model,					\
	.steppings	= _steppings,					\
	.feature	= _feature,					\
	.driver_data	= (अचिन्हित दीर्घ) _data				\
पूर्ण

/**
 * X86_MATCH_VENDOR_FAM_MODEL_FEATURE - Macro क्रम CPU matching
 * @_venकरोr:	The venकरोr name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@_venकरोr
 * @_family:	The family number or X86_FAMILY_ANY
 * @_model:	The model number, model स्थिरant or X86_MODEL_ANY
 * @_feature:	A X86_FEATURE bit or X86_FEATURE_ANY
 * @_data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * The steppings arguments of X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE() is
 * set to wildcards.
 */
#घोषणा X86_MATCH_VENDOR_FAM_MODEL_FEATURE(venकरोr, family, model, feature, data) \
	X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE(venकरोr, family, model, \
						X86_STEPPING_ANY, feature, data)

/**
 * X86_MATCH_VENDOR_FAM_FEATURE - Macro क्रम matching venकरोr, family and CPU feature
 * @venकरोr:	The venकरोr name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@venकरोr
 * @family:	The family number or X86_FAMILY_ANY
 * @feature:	A X86_FEATURE bit
 * @data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * All other missing arguments of X86_MATCH_VENDOR_FAM_MODEL_FEATURE() are
 * set to wildcards.
 */
#घोषणा X86_MATCH_VENDOR_FAM_FEATURE(venकरोr, family, feature, data)	\
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(venकरोr, family,		\
					   X86_MODEL_ANY, feature, data)

/**
 * X86_MATCH_VENDOR_FEATURE - Macro क्रम matching venकरोr and CPU feature
 * @venकरोr:	The venकरोr name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@venकरोr
 * @feature:	A X86_FEATURE bit
 * @data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * All other missing arguments of X86_MATCH_VENDOR_FAM_MODEL_FEATURE() are
 * set to wildcards.
 */
#घोषणा X86_MATCH_VENDOR_FEATURE(venकरोr, feature, data)			\
	X86_MATCH_VENDOR_FAM_FEATURE(venकरोr, X86_FAMILY_ANY, feature, data)

/**
 * X86_MATCH_FEATURE - Macro क्रम matching a CPU feature
 * @feature:	A X86_FEATURE bit
 * @data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * All other missing arguments of X86_MATCH_VENDOR_FAM_MODEL_FEATURE() are
 * set to wildcards.
 */
#घोषणा X86_MATCH_FEATURE(feature, data)				\
	X86_MATCH_VENDOR_FEATURE(ANY, feature, data)

/**
 * X86_MATCH_VENDOR_FAM_MODEL - Match venकरोr, family and model
 * @venकरोr:	The venकरोr name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@venकरोr
 * @family:	The family number or X86_FAMILY_ANY
 * @model:	The model number, model स्थिरant or X86_MODEL_ANY
 * @data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * All other missing arguments of X86_MATCH_VENDOR_FAM_MODEL_FEATURE() are
 * set to wildcards.
 */
#घोषणा X86_MATCH_VENDOR_FAM_MODEL(venकरोr, family, model, data)		\
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(venकरोr, family, model,	\
					   X86_FEATURE_ANY, data)

/**
 * X86_MATCH_VENDOR_FAM - Match venकरोr and family
 * @venकरोr:	The venकरोr name, e.g. INTEL, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOR_@venकरोr
 * @family:	The family number or X86_FAMILY_ANY
 * @data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * All other missing arguments to X86_MATCH_VENDOR_FAM_MODEL_FEATURE() are
 * set of wildcards.
 */
#घोषणा X86_MATCH_VENDOR_FAM(venकरोr, family, data)			\
	X86_MATCH_VENDOR_FAM_MODEL(venकरोr, family, X86_MODEL_ANY, data)

/**
 * X86_MATCH_INTEL_FAM6_MODEL - Match venकरोr INTEL, family 6 and model
 * @model:	The model name without the INTEL_FAM6_ prefix or ANY
 *		The model name is expanded to INTEL_FAM6_@model पूर्णांकernally
 * @data:	Driver specअगरic data or शून्य. The पूर्णांकernal storage
 *		क्रमmat is अचिन्हित दीर्घ. The supplied value, poपूर्णांकer
 *		etc. is casted to अचिन्हित दीर्घ पूर्णांकernally.
 *
 * The venकरोr is set to INTEL, the family to 6 and all other missing
 * arguments of X86_MATCH_VENDOR_FAM_MODEL_FEATURE() are set to wildcards.
 *
 * See X86_MATCH_VENDOR_FAM_MODEL_FEATURE() क्रम further inक्रमmation.
 */
#घोषणा X86_MATCH_INTEL_FAM6_MODEL(model, data)				\
	X86_MATCH_VENDOR_FAM_MODEL(INTEL, 6, INTEL_FAM6_##model, data)

#घोषणा X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(model, steppings, data)	\
	X86_MATCH_VENDOR_FAM_MODEL_STEPPINGS_FEATURE(INTEL, 6, INTEL_FAM6_##model, \
						     steppings, X86_FEATURE_ANY, data)

/*
 * Match specअगरic microcode revisions.
 *
 * venकरोr/family/model/stepping must be all set.
 *
 * Only checks against the boot CPU.  When mixed-stepping configs are
 * valid क्रम a CPU model, add a quirk क्रम every valid stepping and
 * करो the fine-tuning in the quirk handler.
 */

काष्ठा x86_cpu_desc अणु
	u8	x86_family;
	u8	x86_venकरोr;
	u8	x86_model;
	u8	x86_stepping;
	u32	x86_microcode_rev;
पूर्ण;

#घोषणा INTEL_CPU_DESC(model, stepping, revision) अणु		\
	.x86_family		= 6,				\
	.x86_venकरोr		= X86_VENDOR_INTEL,		\
	.x86_model		= (model),			\
	.x86_stepping		= (stepping),			\
	.x86_microcode_rev	= (revision),			\
पूर्ण

बाह्य स्थिर काष्ठा x86_cpu_id *x86_match_cpu(स्थिर काष्ठा x86_cpu_id *match);
बाह्य bool x86_cpu_has_min_microcode_rev(स्थिर काष्ठा x86_cpu_desc *table);

#पूर्ण_अगर /* _ASM_X86_CPU_DEVICE_ID */
