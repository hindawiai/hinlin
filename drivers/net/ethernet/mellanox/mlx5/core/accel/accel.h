<शैली गुरु>
#अगर_अघोषित __MLX5E_ACCEL_H__
#घोषणा __MLX5E_ACCEL_H__

#अगर_घोषित CONFIG_MLX5_ACCEL

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>

अटल अंतरभूत bool is_metadata_hdr_valid(काष्ठा sk_buff *skb)
अणु
	__be16 *ethtype;

	अगर (unlikely(skb->len < ETH_HLEN + MLX5E_METADATA_ETHER_LEN))
		वापस false;
	ethtype = (__be16 *)(skb->data + ETH_ALEN * 2);
	अगर (*ethtype != cpu_to_be16(MLX5E_METADATA_ETHER_TYPE))
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत व्योम हटाओ_metadata_hdr(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *old_eth;
	काष्ठा ethhdr *new_eth;

	/* Remove the metadata from the buffer */
	old_eth = (काष्ठा ethhdr *)skb->data;
	new_eth = (काष्ठा ethhdr *)(skb->data + MLX5E_METADATA_ETHER_LEN);
	स_हटाओ(new_eth, old_eth, 2 * ETH_ALEN);
	/* Ethertype is alपढ़ोy in its new place */
	skb_pull_अंतरभूत(skb, MLX5E_METADATA_ETHER_LEN);
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ACCEL */

#पूर्ण_अगर /* __MLX5E_EN_ACCEL_H__ */
