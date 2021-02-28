# Ising-model-simulation
Repository for my graduation paper about two dimensional ising model

# Machine Learning implementation of two dimensional Ising Model

![Ising model configuration](https://drive.google.com/uc?export=view&id=1pgcDs7d0tehYxTCzJXnZGoxsYmqeuIjT)

이징 모형(Ising model)은 자성에 관한 통계역학적 모델이다. 각각의 원자들은 자기 모멘트(magnetic moment), 즉 spin을 가지고 있으며 ising model에서 원자의 스핀은 up, down 두 종류로 제한된다. 전체적인 자성의 밀도가 유의미한 방향을 가진다면 Ferromagnetic state, 그렇지 않다면 Paramagnetic state 라고 한다. 주어진 2차원 정방형의 이징 배열에 대하여 Metropolis-Hastings 알고리즘을 적용함으로써 특정한 온도 조건에서 이에 대응하는 자연스러운 ising configuration을 얻을 수 있다. 이러한 ising configuration에 대하여 Energy, Magnetization, Specific heat, Susceptability를 계산한 결과는 다음과 같다.

![Simulation result](https://drive.google.com/uc?export=view&id=1-1s8Zz4lWPdfpM_j0qShzyjVvcM9wQjQ)

Metropolis 알고리즘의 결과를 보면 ising configuration은 특정한 온도를 경계로 급격한 상전이(Phase transition)가 발생하고 있음을 알 수 있다. 즉, 저온에서 고온으로 온도가 증가함에 따라 에너지는 서서히 증가하고, 자성은 특정한 임계온도를 중심으로 급격히 감소한다. ising configuration을 온도 조건에 따라 시각화하여 그 변화를 명확히 확인할 수 있다.

![ising configuration](https://drive.google.com/uc?export=view&id=1FFjoqyKrfYWhq2Gn6XzS_8cH8WVEPhTc)

위 그림을 보면 ising configuration은 특정한 임계온도(Quiri Temperature)를 경계로 Phase가 구분되는 것을 알 수 있다. 본 연구의 목적은 이징 모형의 자성 변화에 따른 Phase 구분을 인공 신경망을 활용한 학습을 통해 분류해낼 수 있는가를 확인하는 것이었다. 이와 관련하여 본 실험에서는 대규모의 ising 배열을 생성하여 이를 2차원 이미지로 간주하고, 각각의 이미지에 정답을 의미하는 자성 라벨을 태깅하였다. 인공 신경망은 이러한 이미지 vs 라벨 구조를 학습하였고, 최종적으로 Test data에 대한 인공 신경망의 성능 확인이 이루어졌다.

![Classfication result](https://drive.google.com/uc?export=view&id=1EM4rLSCwmr5lX2Fs_wBpysj0b0qx22a9)

최종적으로 위 그림과 같은 분류를 인공 신경망이 해내었음을 알 수 있었다.
