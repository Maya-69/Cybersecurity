# Cipher 1 - Monoalphabetic Substitution Cipher Solution

## Original Encrypted Text

```
dkxyvrh 1 - qegt vkr hxccwv keur: xuwdr wn cehrq nwvvwtp et vkr hwsrhcxto gwvk krh nwnvrh, gkrt nkr tevwdrn x vxuowtp, duevkrq gkwvr hxccwv gwvk x yedorv gxvdk hit yxnv. nkr leuuegn wv qegt x hxccwv keur gkrt niqqrtub nkr lxuun x uetp gxb ve x dihwein kxuu gwvk fxtb uedorq qeehn el xuu nwmrn. nkr lwtqn x nfxuu orb ve x qeeh vee nfxuu leh krh ve lwv, civ vkheipk gkwdk nkr nrrn xt xvvhxdvwsr pxhqrt. nkr vkrt qwndesrhn x cevvur uxcruurq 'qhwto fr', vkr detvrtvn el gkwdk dxinr krh ve nkhwto vee nfxuu ve hrxdk vkr orb. x dxor gwvk 'rxv fr' et wv dxinrn krh ve pheg ve nidk x vhrfrtqein nwmr krh krxq kwvn vkr drwuwtp.
```

## Decryption Progress

### Step 1: Reveal **X → J, C → Y, D → B, Q → C**

```
__j____ _ - ce__ ___ __yy__y ____: j__b_ __ yoh__ _______ __ ___ ___________ ____ ___ _______, ____ ___ _______ _ _______, b_____q _____ __yy__y ____ _ ______ _____ ___ _____. ___ _______ __ ce__ _ __yy__y ____ ____ _______ ___ _____ _ ____ ___ __ _ b_______ ____ ____ _____ _____ __ ___ ______. ___ _____ _ _____ ___ __ _ ceeh ___ _____ ___ ___ __ ____ ___ _____ _______ ____ ___ ____ __ _________ ____c_. ___ ____ _________ _ ______ _______ 'c____ __', ___ ________ __ _____ _____ ___ __ _____ ___ _____ __ _____ ___ ___. _ b___ ____ '_____ __' __ __ ______ ___ __ ____ __ ____ _ ___________ ____ ___ ____ ____ ___ _______.
```

*Changed: X → J, C → Y, D → B, Q → C*

### Step 2: Reveal **X → J, C → Y, D → B, Q → C, R → O, L → M, P → W, K → R, W → U, A → Q, O → H**

```
__j____ _ - ce__ vkr __yy__y ____: q__b_ __ yoh_c _______ __ ___ ___________ u___ ___ _______, ____ ___ _______ _ q_______, b_____o g____ __yy__y u___ q ______ _____ ___ _____. ___ _______ __ ce__ q __yy__y ____ ____ _icc_t__ ___ _____ _ ____ ___ __ q b_______ ____ u___ _____ _____ __ ___ ______. ___ _w_o_ q _____ ___ __ q ceeh ___ _____ ___ ___ __ ____ ___ _____ _______ ____ ___ ____ __ _________ ____c_. ___ ____ _________ q ______ _______ 'c____ __', ___ ________ __ u___ _____ ___ __ _____ ___ _____ __ _____ ___ ___. q b___ u___ '_____ __' __ __ ______ ___ __ ____ __ ____ q ___________ ____ ___ ____ ____ ___ _______.
```

*Changed: R → O, L → M, P → W, K → R, W → U, A → Q, O → H*

### Step 3: **All Letters Substituted**

```
ch__t__ _ - __wn _h_ ___bb__ h___: _lic_ i_ __r_d ___t____ __ th_ ___v_____k __th h__ ___t__, wh__ _h_ __tic__ _ t_lki__,  cl_th_d whi__ ___bi_ __th _ p_ck__ w_tch __n p__t. _h_ f_ll_w_ it d_wn _ ___bi_ h_l_ wh__ ____d_nly _h_ f_ll_ _ l_ng w_y t_ _ c_ri__ h_ll __th m_ny l_ck_d d____ _f _ll _i___. _h_ find_ _ _m_ll k_y t_ _ d__r t__ _m_ll f_r h_r t_ fit, b_t thr__gh whi_h _h_ ___ _n _tt___tiv_ g_rd_n. _h_ th_n di_c_v_r_ _ b_ttl_ l_b_ll_d 'drink m_', th_ c_nt_nt_ _f whi_h c_u__ h_r t_ _hrink t__ _m_ll t_ r__ch th_ k_y. _ c_k_ __th '_t m_' _n it c_u___ h_r t_ gr_w t_ _u_h _ tr_m_nd__ _i__ h_r h__d hit_ th_ c_ili__.
```

*Changed: All remaining letters substituted*

## Cipher Solution

### Encryption Alphabet
```
XCDQRLPKWAOUFTEYJHNVISGZBM
```

### Decryption Alphabet (Reciprocal)
```
JYBCOMWRUQHFZSKGDEVNLTIAPX
```

### Analysis

This is a monoalphabetic substitution cipher, where each plaintext letter is consistently mapped to a single ciphertext letter. The reciprocal alphabet provided allows for direct decryption of the ciphertext. By matching each ciphertext character to its corresponding plaintext character in the decryption mapping, the full message can be systematically recovered. Once the complete substitution key is known, all letters decrypt cleanly to reveal the original plaintext without ambiguity.

## Fully Decrypted Text

```
CHAPTER 1 - DOWN THE RABBIT HOLE: ALICE IS BORED SITTING ON THE RIVERBANK WITH HER SISTER, WHEN SHE NOTICES A TALKING, CLOTHED WHITE RABBIT WITH A POCKET WATCH RUN PAST. SHE FOLLOWS IT DOWN A RABBIT HOLE WHEN SUDDENLY SHE FALLS A LONG WAY TO A CURIOUS HALL WITH MANY LOCKED DOORS OF ALL SIZES. SHE FINDS A SMALL KEY TO A DOOR TOO SMALL FOR HER TO FIT, BUT THROUGH WHICH SHE SEES AN ATTRACTIVE GARDEN. SHE THEN DISCOVERS A BOTTLE LABELLED 'DRINK ME', THE CONTENTS OF WHICH CAUSE HER TO SHRINK TOO SMALL TO REACH THE KEY. A CAKE WITH 'EAT ME' ON IT CAUSES HER TO GROW TO SUCH A TREMENDOUS SIZE HER HEAD HITS THE CEILING.
```
