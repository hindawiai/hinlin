<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित __USB_TYPEC_MUX
#घोषणा __USB_TYPEC_MUX

#समावेश <linux/property.h>
#समावेश <linux/usb/typec.h>

काष्ठा device;
काष्ठा typec_mux;
काष्ठा typec_चयन;
काष्ठा typec_alपंचांगode;
काष्ठा fwnode_handle;

प्रकार पूर्णांक (*typec_चयन_set_fn_t)(काष्ठा typec_चयन *sw,
				     क्रमागत typec_orientation orientation);

काष्ठा typec_चयन_desc अणु
	काष्ठा fwnode_handle *fwnode;
	typec_चयन_set_fn_t set;
	स्थिर अक्षर *name;
	व्योम *drvdata;
पूर्ण;

काष्ठा typec_चयन *fwnode_typec_चयन_get(काष्ठा fwnode_handle *fwnode);
व्योम typec_चयन_put(काष्ठा typec_चयन *sw);
पूर्णांक typec_चयन_set(काष्ठा typec_चयन *sw,
		     क्रमागत typec_orientation orientation);

अटल अंतरभूत काष्ठा typec_चयन *typec_चयन_get(काष्ठा device *dev)
अणु
	वापस fwnode_typec_चयन_get(dev_fwnode(dev));
पूर्ण

काष्ठा typec_चयन *
typec_चयन_रेजिस्टर(काष्ठा device *parent,
		      स्थिर काष्ठा typec_चयन_desc *desc);
व्योम typec_चयन_unरेजिस्टर(काष्ठा typec_चयन *sw);

व्योम typec_चयन_set_drvdata(काष्ठा typec_चयन *sw, व्योम *data);
व्योम *typec_चयन_get_drvdata(काष्ठा typec_चयन *sw);

काष्ठा typec_mux_state अणु
	काष्ठा typec_alपंचांगode *alt;
	अचिन्हित दीर्घ mode;
	व्योम *data;
पूर्ण;

प्रकार पूर्णांक (*typec_mux_set_fn_t)(काष्ठा typec_mux *mux,
				  काष्ठा typec_mux_state *state);

काष्ठा typec_mux_desc अणु
	काष्ठा fwnode_handle *fwnode;
	typec_mux_set_fn_t set;
	स्थिर अक्षर *name;
	व्योम *drvdata;
पूर्ण;

काष्ठा typec_mux *fwnode_typec_mux_get(काष्ठा fwnode_handle *fwnode,
				       स्थिर काष्ठा typec_alपंचांगode_desc *desc);
व्योम typec_mux_put(काष्ठा typec_mux *mux);
पूर्णांक typec_mux_set(काष्ठा typec_mux *mux, काष्ठा typec_mux_state *state);

अटल अंतरभूत काष्ठा typec_mux *
typec_mux_get(काष्ठा device *dev, स्थिर काष्ठा typec_alपंचांगode_desc *desc)
अणु
	वापस fwnode_typec_mux_get(dev_fwnode(dev), desc);
पूर्ण

काष्ठा typec_mux *
typec_mux_रेजिस्टर(काष्ठा device *parent, स्थिर काष्ठा typec_mux_desc *desc);
व्योम typec_mux_unरेजिस्टर(काष्ठा typec_mux *mux);

व्योम typec_mux_set_drvdata(काष्ठा typec_mux *mux, व्योम *data);
व्योम *typec_mux_get_drvdata(काष्ठा typec_mux *mux);

#पूर्ण_अगर /* __USB_TYPEC_MUX */
