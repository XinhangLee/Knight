# Knight
> This is a project based on the game ***Soul Knight***, and is configured via **SDL**.

---

## 项目框架

```markdown
Knight/
│
├── README.md
│
├── head/
│   ├── common.h
│   └── main.h
│
├── rsc/
│
├── src/
│   └── main.c
│
└── .gitignore
```
---

## 游戏元素

### 人物

```c++
class Hero{
    int HP;
    int Shield;
    int Energy;
    Weapon weapon;
public:
    Hero();
    ~Hero();
    void Move();
    void Attack();
}
```

### 怪物
```c++
class Monsters{
    int HP;
    int Energy;
    Weapon weapon;
public:
    Monster();
    ~Monster();
    void Move();
    void Attack();
}
```
### 武器
```c++
struct Weapon{
    int AttackPower;
    int EnergyConsumed;
    int speed;
}
```
### 杂项
#### 菜单
#### 地牢场景
#### 功能性页面

---

## 游戏指南

> ***For You***:
> 
>   诸君，于游戏之境，且行且赏，领略其中雅趣，方不负此番妙境。