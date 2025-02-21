# 🎮 Mean Thoughts - Platformer Game

Mean Thoughts est un jeu de plateforme écrit en C utilisant **SDL2**.  
Ce projet inclut également un système de **tests unitaires** avec **Criterion**.

---

## 📦 Installation des dépendances

### 🛠️ **1. Installer Homebrew (si ce n'est pas encore fait)**
Si Homebrew n'est pas installé :
```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 🏠 **2. Installer les dépendances système**
```sh
brew install sdl2 sdl2_image criterion
```

Cela installe :
- **SDL2** (pour le rendu graphique)
- **SDL2_image** (pour charger des images)
- **Criterion** (pour les tests unitaires)

Si tu es sur **Linux (Debian/Ubuntu)** :
```sh
sudo apt install libsdl2-dev libsdl2-image-dev criterion-dev
```

---

## 🏰 Compilation du projet

### ▶️ **1. Compiler et lancer le jeu**
```sh
make
./platformer
```

### 🪑 **2. Nettoyer les fichiers compilés**
```sh
make clean
```

---

## ✅ Exécution des tests unitaires

### 🧪 **1. Compiler et exécuter les tests**
```sh
make run-tests
```

### 🪑 **2. Nettoyer les fichiers de test**
```sh
make clean-tests
```

---

## 📂 Structure du projet

```
/projet
 ├── src/                  # Code source du jeu
 │   ├── components/       # Modules spécifiques (ex: map)
 │   ├── legacy/           # legacy
 │   ├── main.c            
 │   ├── game.c            # Boucle principale du jeu
 │   ├── renderer.c        # Gestion du rendu SDL
 │   ├── background.c      
 ├── tests/                # Fichiers de tests
 │   ├── tests.c        
 ├── Makefile              # Fichier de compilation
```

---

## 🚀 Développement & Contribution

### 🔧 **1. Cloner le projet**
```sh
git clone https://github.com/ton-user/mean-thoughts.git
cd mean-thoughts
```

### 💡 **2. Modifier le code**
Développe de nouvelles fonctionnalités ou corrige des bugs.

### 🧪 **3. Tester tes modifications**
Avant de commit tes changements, exécute :
```sh
make run-tests
```

### 🚀 **4. Proposer une contribution**
Crée une **pull request** avec tes modifications.

---

## ❓ Problèmes fréquents & solutions

### **🟥 `ld: library 'criterion' not found` lors des tests**
🔷 **Solution** : Vérifie que la bibliothèque est bien installée :
```sh
ls /opt/homebrew/lib/libcriterion.dylib
```
Si elle n'est pas trouvée :
```sh
brew link --overwrite criterion
```

### **🟥 `Undefined symbols for architecture arm64`**
🔷 **Solution** : Ajoute les bibliothèques SDL2 dans `LDFLAGS` et `TEST_LDFLAGS` du `Makefile`.

---

## 🌟 Licence

📝 Ce projet est sous licence MIT.

