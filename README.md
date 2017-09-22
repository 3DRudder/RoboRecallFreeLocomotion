# 3dRudder custom theme based on jekyll theme [slate](https://pages-themes.github.io/slate/)

# Get theme in other repo

* Create new branch: "gh-pages",
* add remote "pages" : ```git remote add pages git@github.com:3DRudder/3dRudder.github.io.git```,
* git fetch pages,
* pull/merge "pages" into branch "gh-pages" : ```git pull -Xours pages master --allow-unrelated-histories```
* copy/past the content of master "ReadMe.md" into the "index.md"
* Add in _config.yml 
  * ```repository: 3dRudder/name_of_repo```
  * ```show_downloads: "true"```
  * comment ```#title: [3dRudder Repositories]``` or modify ```title: [3dRudder the_project_name]```
* push (maybe force push if fail)
* look the result on browser ```3dRudder.github.io/name_of_repo```

# Update theme

* go to your "gh-pages" branch
* pull/merge : ```git pull -Xours pages master --allow-unrelated-histories```
* copy/past the content of master "ReadMe.md" into the "index.md"
* push

# Test in local

* Open cmd or bash on root of project
* Check ruby is installed : ```ruby --version``` ([ruby installer](https://rubyinstaller.org/downloads/))
* Install bundle : ```bundle install```
-> si ne fonctionne pas, lancer ```gem install bundler```
* Install jekyll : ```gem install jekyll bundler```
* Add in .gitignore 
  * ```_site/```
  * ```Gemfile.lock```
  * ```.gem```
* Launch server : ```bundle exec jekyll serve```
* Test : http://127.0.0.1:4000/

ref. https://help.github.com/articles/setting-up-your-github-pages-site-locally-with-jekyll/

# Soon
* launch .bat or .cmd to update automaticaly

# Tools
* https://help.github.com/articles/repository-metadata-on-github-pages/

# Update Main List
* Modify and commit thids file (ReadMe)
